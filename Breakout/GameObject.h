#pragma once
#include "GlobalConsts.h"
#include "Collider.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual sf::Text GetText() { return m_Text; }
	virtual sf::RectangleShape GetRectangle() {	return m_Shape;}
	virtual sf::CircleShape GetBall() { return m_BallShape; }
	//tried using just the one update position for ball and paddle here. wouldnt work
	virtual void UpdatePosition(sf::Time& deltaTime) {}
	virtual void UpdatePosition(sf::Vector2f newPosition) {}
	virtual void UpdatePosition(sf::Vector2i mousePos) {}
	virtual void UpdatePosition(Collider& collider) {};
	virtual void PaddleHit(sf::Vector2f) {};


	
protected:
	sf::Vector2f m_NewVelocity;
	sf::Color m_Color;
	sf::Vector2f m_Size;
	sf::Text m_Text;
	sf::RectangleShape m_Shape;
	sf::CircleShape m_BallShape;
	sf::Vector2f m_Velocity;
};

