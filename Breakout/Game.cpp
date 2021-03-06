#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	Init();
}

void Game::Init()
{
	GameState m_GameState = GameState::STARTMENU;
	
}

Game::~Game()
{
}

void Game::CreateText()
{
	std::shared_ptr<GameObject> _tempText(new TextObject("BREAKOUT!", sf::Color::Red, sf::Vector2f(100, 100), 200));
	m_GameObjectVector.push_back(_tempText);
	_tempText.reset(new TextObject("Press Spacebar to continue\n  Escape to exit anytime", sf::Color::Green, sf::Vector2f(175, 500), 60));
	m_GameObjectVector.push_back(_tempText);
}

void Game::CreateLives()
{	
	for (int i = 1150; i > 1001; i -= 50)
	{
		std::shared_ptr<GameObject> _tempBall(new BallObject(sf::Vector2f(i, 700), 10.f, sf::Color::Red));
		m_GameObjectVector.push_back(_tempBall);
	}
}

void Game::CreateBall()
{
	std::shared_ptr<GameObject> _tempBall(new BallObject(sf::Vector2f(600, 625), 10.f, sf::Color::Red));
	m_GameObjectVector.push_back(_tempBall);
}

void Game::CreateArena()
{
	sf::Vector2f vecArray[5];
	vecArray[0] = sf::Vector2f(20, WINDOWHEIGHT + 200);  //vertical size
	vecArray[1] = sf::Vector2f(WINDOWWIDTH + 200, 20);  //horizontal size		  
	vecArray[2] = sf::Vector2f(10, WINDOWHEIGHT / 2.f); // left 
	vecArray[3] = sf::Vector2f(WINDOWWIDTH / 2.f, 10); // top start locations
	vecArray[4] = sf::Vector2f(WINDOWWIDTH - 10, WINDOWHEIGHT / 2.f); // right start location
	std::shared_ptr<GameObject> _tempBlock;

	for (int iter = 2; iter < 6; iter++)
	{
		_tempBlock.reset(new ArenaBlockObject(vecArray[(iter % 2)], vecArray[iter], sf::Color(200,220,250)));
		m_GameObjectVector.push_back(_tempBlock);
	}
}

void Game::CreatePaddle()
{
	std::shared_ptr<GameObject> _tempPaddle(new PaddleObject(sf::Vector2f(600,650), sf::Vector2f(160,16),sf::Color::White));
	m_GameObjectVector.push_back(_tempPaddle);

}

void Game::Update(sf::RenderWindow &window)
{
	m_DeltaTime = m_Clock.restart();
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
	InputHandler(window);
	switch (m_GameState)
	{
	case Game::GameState::STARTMENU:
		if (!m_GameObjectVector.empty())
		{
			m_GameObjectVector.clear();
		}
		CreateText();
		CreateLives();
		CreateBall();
		CreatePaddle();
		CreateArena();
		m_CurrentLevel = 1;
		m_Lives = 3;
		LoadLevel();		break;
	case Game::GameState::PREPLAYING:
		m_GameObjectVector[PADDLE]->UpdatePosition(localMouse);
		m_GameObjectVector[BALL]->UpdatePosition(localMouse);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_GameState = GameState::PLAYING;
		}
		break;
	case Game::GameState::PLAYING:
		m_GameObjectVector[BALL]->UpdatePosition(m_DeltaTime);
		m_GameObjectVector[PADDLE]->UpdatePosition(localMouse);

		for (int iter = PADDLE; iter < MAXOBJECTS; iter++)
		{
			if (m_GameObjectVector[iter] != nullptr)
			{
				n_Collision = m_Collider.CheckCollision(&m_GameObjectVector[BALL]->GetBall(), &m_GameObjectVector[iter]->GetRectangle());				
				if (iter > FIRSTBREAKBLOCK && n_Collision)
				{
					m_GameObjectVector[iter] = nullptr;
				}
				else if (iter == PADDLE && n_Collision)
				{
					m_Collider.SetContactPaddle(true);
				}
			}
			else
			{
				m_NullCount++;
				if (m_NullCount == 220)
				{
					m_GameObjectVector.resize(11);
					m_CurrentLevel++;
					m_GameState = GameState::ENDLEVEL;
				}
			}
		}
		m_NullCount = 0;
		if (m_Collider.GetContactPaddle())
		{
			m_GameObjectVector[BALL]->PaddleHit(m_GameObjectVector[PADDLE]->GetRectangle().getPosition());
		}
		else
		{
			m_GameObjectVector[BALL]->UpdatePosition(m_Collider);
		}
		m_Collider.SetAllContactsFalse();
		n_Collision = false;
		if (m_GameObjectVector[BALL]->GetBall().getPosition().y > 750)
		{
			m_Lives--;
			m_GameObjectVector[m_Lives + 2] = nullptr;
			if (m_Lives > 0)
			{
				m_GameState = GameState::PREPLAYING;
			}
			else
			{
				m_GameState = GameState::GAMEOVER;
			}
		}
		break;
	case Game::GameState::ENDLEVEL:
		LoadLevel();
		break;
	case Game::GameState::GAMEOVER:
		break;
	default:
		break;
	}
}

void Game::InputHandler(sf::RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}
	localMouse = GetMousePosition(window);
	switch (m_GameState)
	{
	case GameState::STARTMENU:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			m_GameState = GameState::PREPLAYING;
		break;
	case GameState::PREPLAYING:
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_GameState = GameState::PLAYING;
		}
		break;
	case GameState::PLAYING:
		break;
	case GameState::ENDLEVEL:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_GameState = GameState::PREPLAYING;
		}
		break;
	case GameState::GAMEOVER:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_GameState = GameState::STARTMENU;
		}
		break;
	default:
		break;
	}
}
void Game::Draw(sf::RenderWindow &window)
{
	window.clear();
	switch (m_GameState)
	{
	case GameState::STARTMENU:
		window.draw(m_GameObjectVector[BREAKOUT]->GetText());
		window.draw(m_GameObjectVector[CONTINUE]->GetText());
		break;
	case GameState::PREPLAYING:
		DrawAll(window);
		break;
	case GameState::PLAYING:
		DrawAll(window);
		break;
	case GameState::ENDLEVEL:
		DrawBasic(window);
		window.draw(m_GameObjectVector[CONTINUE]->GetText());
		break;
	case GameState::GAMEOVER:
		DrawBasic(window);
		window.draw(m_GameObjectVector[BREAKOUT]->GetText());
		window.draw(m_GameObjectVector[CONTINUE]->GetText());
		break;
		break;
	default:
		break;
	}
	window.display();
}

void Game::DrawBasic(sf::RenderWindow &window)
{
	for (int iter = LIFEONE; iter < PADDLE; iter++)
	{
		if (m_GameObjectVector[iter] != nullptr)
		{
			window.draw(m_GameObjectVector[iter]->GetBall());
		}
	}
	for (int iter = PADDLE; iter < FIRSTBREAKBLOCK; iter++)
	{
		if (m_GameObjectVector[iter] != nullptr)
			window.draw(m_GameObjectVector[iter]->GetRectangle());
	}
}

void Game::DrawAll(sf::RenderWindow & window)
{
	for (int iter = LIFEONE; iter < PADDLE; iter++)
	{
		if (m_GameObjectVector[iter] != nullptr)
		{
			window.draw(m_GameObjectVector[iter]->GetBall());
		}
	}
	for (int iter = PADDLE; iter < MAXOBJECTS; iter++)
	{
		if (m_GameObjectVector[iter] != nullptr)
			window.draw(m_GameObjectVector[iter]->GetRectangle());
	}
}

void Game::LoadLevel()
{
	switch (m_CurrentLevel)
	{
	case 1:
		if (!m_Populater.LoadFromFile("Media/level3.txt", sf::Vector2f(50, 30), m_GameObjectVector))
			printf("Error Populating\n");
		break;
	case 2:
		if (!m_Populater.LoadFromFile("Media/level1.txt", sf::Vector2f(50, 30), m_GameObjectVector))
			printf("Error Populating\n");
		break;
	case 3:
		if (!m_Populater.LoadFromFile("Media/level2.txt", sf::Vector2f(50, 30), m_GameObjectVector))
			printf("Error Populating\n");
		break;
	case 4:
		m_GameState = GameState::STARTMENU;
		m_CurrentLevel = 1;
		if (!m_Populater.LoadFromFile("Media/basiclevel.txt", sf::Vector2f(50, 20), m_GameObjectVector))
			printf("Error Populating\n");
		break;
	default:
		break;
	}
}

sf::Vector2i Game::GetMousePosition(sf::RenderWindow & window)
{
	sf::Vector2i _windowBorderOffset = sf::Vector2i(4, 28);
	sf::Vector2i _globalMousePos = sf::Mouse::getPosition();
	_globalMousePos -= window.getPosition();
	_globalMousePos -= _windowBorderOffset;
	return _globalMousePos;
}


