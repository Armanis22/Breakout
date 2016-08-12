#pragma once
#include "GameObject.h"
class BallObject :
	public GameObject
{
public:
	BallObject(sf::Vector2f pos, float radius, sf::Color color);
	~BallObject();

	virtual sf::CircleShape GetBall() { return m_BallShape; }
	void UpdatePosition(sf::Time& deltaTime);


private:
	sf::CircleShape m_BallShape;
};

