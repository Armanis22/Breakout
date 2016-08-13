#include "stdafx.h"
#include "ArenaBlockObject.h"


ArenaBlockObject::ArenaBlockObject(sf::Vector2f size, sf::Vector2f pos, sf::Color color)
{	
	m_Shape.setPosition(pos);
	m_Shape.setSize(size);
	m_Shape.setFillColor(color);
	m_Shape.setOrigin(sf::Vector2f(size.x/2.f,size.y/2.f));

}


ArenaBlockObject::~ArenaBlockObject()
{
}
