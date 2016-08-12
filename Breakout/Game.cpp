#include "stdafx.h"
#include "Game.h"
#include "GameObject.h"

Game::Game()
{
	Init();
}

void Game::Init()
{
	GameState m_GameState = GameState::STARTMENU;

	CreateText();
	CreateBall();
	CreatePaddle();
	CreateArena();
}

Game::~Game()
{
}

void Game::CreateText()
{
	std::shared_ptr<TextObject> _tempText(new TextObject("BREAKOUT!", sf::Color::Red, sf::Vector2f(100, 100), 200));
	m_GameObjectVector.push_back(_tempText);
	_tempText.reset(new TextObject("Press Spacebar to continue\n  Escape to exit anytime", sf::Color::Green, sf::Vector2f(175, 500), 60));
	m_GameObjectVector.push_back(_tempText);
}

void Game::CreateBall()
{
	std::shared_ptr<BallObject> _tempBall(new BallObject(sf::Vector2f(600, 630), 10.f, sf::Color::White));
	m_GameObjectVector.push_back(_tempBall);
}

void Game::CreateArena()
{
	sf::Vector2f vecArray[5];
	vecArray[0] = sf::Vector2f(20, 750);  //vertical size
	vecArray[1] = sf::Vector2f(1200, 20);  //horizontal size		  
	vecArray[2] = sf::Vector2f(0, 0); // top and left start locations
	vecArray[3] = sf::Vector2f(0, 0); // top and left start locations
	vecArray[4] = sf::Vector2f(1180, 0); // right start location
	std::shared_ptr<ArenaBlockObject> _tempBlock;

	for (int iter = 2; iter < 5; iter++)
	{
		_tempBlock.reset(new ArenaBlockObject(vecArray[(iter % 2)], vecArray[iter], sf::Color(200,220,250)));
		m_GameObjectVector.push_back(_tempBlock);
	}
}

void Game::CreatePaddle()
{
	std::shared_ptr<PaddleObject> _tempPaddle(new PaddleObject(sf::Vector2f(600,650), sf::Vector2f(80,10),sf::Color::White));
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
	for (int iter = 2; iter < 4; iter++)
	{
		m_GameObjectVector[iter]->UpdatePosition(m_DeltaTime);
	}
}

void Game::InputHandler(sf::RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}
	switch (m_GameState)
	{
	case GameState::STARTMENU:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			m_GameState = GameState::PLAYING;
		break;
	case GameState::PLAYING:
		break;
	case GameState::ENDLEVEL:
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
		window.draw(m_GameObjectVector[0]->GetText());
		window.draw(m_GameObjectVector[1]->GetText());
		break;
	case GameState::PLAYING:
		window.draw(m_GameObjectVector[2]->GetBall());
		for (int iter = 3; iter < 7; iter++)
		{
			window.draw(m_GameObjectVector[iter]->GetRectangle());
		}
		break;
	case GameState::ENDLEVEL:
		break;
	case GameState::GAMEOVER:
		break;
	default:
		break;
	}
	window.display();
}

