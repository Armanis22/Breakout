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
#include "Collider.h"
#include "BlockPopulate.h"
#include <iostream>

class Game
{
public:
	Game();
	void Init();
	~Game();
	void CreateText();
	void CreateLives();
	void CreateBall();
	void CreateArena();
	void CreatePaddle();
	void Update(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);
	void DrawBasic(sf::RenderWindow &window);
	void DrawAll(sf::RenderWindow &window);
	void LoadLevel();

	BlockPopulate m_Populater;

	//needed for pointer to window passing
	sf::Vector2i GetMousePosition(sf::RenderWindow& window);

private:
	void InputHandler(sf::RenderWindow &window);
	std::vector<std::shared_ptr<GameObject>> m_GameObjectVector;

	sf::Time m_DeltaTime;
	sf::Clock m_Clock;
	sf::Vector2i localMouse;
	Collider m_Collider;
	bool n_Collision;
	
	int m_NullCount;
	int m_CurrentLevel;
	int m_Lives;

	enum class GameState {
		STARTMENU,
		PREPLAYING,
		PLAYING,
		ENDLEVEL,
		GAMEOVER
	};
	GameState m_GameState;
};

