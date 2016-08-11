#include "stdafx.h"
#include "ArenaBlockObject.h"


ArenaBlockObject::ArenaBlockObject(sf::Vector2f size, sf::Vector2f pos, sf::Color color)
{	
	m_Shape.setPosition(pos);
	m_Shape.setSize(size);
	m_Shape.setFillColor(color);
}


ArenaBlockObject::~ArenaBlockObject()
{
}
