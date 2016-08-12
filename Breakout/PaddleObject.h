#pragma once
#include "GameObject.h"
class PaddleObject :
	public GameObject
{
public:
	PaddleObject(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	~PaddleObject();

	void UpdatePosition(sf::Time& deltaTime);
	sf::RectangleShape GetRectangle() { return m_Shape; }


};

