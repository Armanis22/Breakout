#include "stdafx.h"
#include "PaddleObject.h"


PaddleObject::PaddleObject(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	m_Shape.setPosition(pos);
	m_Shape.setSize(size);
	m_Shape.setFillColor(color);
	m_Shape.setOrigin(sf::Vector2f(size.x/2,size.y/2));
}


PaddleObject::~PaddleObject()
{
}

void PaddleObject::UpdatePosition(sf::Vector2i mousePos)
{
	mousePos.y = m_Shape.getPosition().y;
	m_Shape.setPosition(static_cast<sf::Vector2f>(mousePos));
	if (m_Shape.getPosition().x < 100)
		m_Shape.setPosition(100, mousePos.y);
	if (m_Shape.getPosition().x > 1100)
		m_Shape.setPosition(1100, mousePos.y);
}


