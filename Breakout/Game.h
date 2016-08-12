#pragma once
#include "stdafx.h"
#include <vector>
#include <memory>
#include "GameObject.h"
#include "TextObject.h"
#include "ArenaBlockObject.h"
#include "PaddleObject.h"
#include "BallObject.h"
#include <string>

class Game
{
public:
	Game();
	void Init();
	~Game();
	void CreateText();
	void CreateBall();
	void CreateArena();
	void CreatePaddle();
	void Update(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);


private:
	void InputHandler(sf::RenderWindow &window);
	std::vector<std::shared_ptr<GameObject>> m_GameObjectVector;

	sf::Time m_DeltaTime;
	sf::Clock m_Clock;

	enum class GameState {
		STARTMENU,
		PLAYING,
		ENDLEVEL,
		GAMEOVER
	};
	GameState m_GameState;
};
