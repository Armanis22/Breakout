#pragma once
#include "GameObject.h"
class ArenaBlockObject :
	public GameObject
{
public:
	ArenaBlockObject(sf::Vector2f size, sf::Vector2f pos, sf::Color color);
	~ArenaBlockObject();

	sf::RectangleShape GetRectangle() { return m_Shape; }

private:
	sf::RectangleShape m_Shape;
};

