#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "GlobalConsts.h"

class BallObject :
	public GameObject
{
public:
	BallObject(sf::Vector2f pos, float radius, sf::Color color);
	~BallObject();
	
	virtual sf::CircleShape GetBall() { return m_BallShape; }
	void UpdatePosition(sf::Time& deltaTime);
	void UpdatePosition(Collider& collider);
	void UpdatePosition(sf::Vector2i mousePos);
	void PaddleHit(sf::Vector2f paddlePos);

private:
	sf::CircleShape m_BallShape;


};

