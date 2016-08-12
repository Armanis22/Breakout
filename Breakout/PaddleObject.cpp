#include "stdafx.h"
#include "PaddleObject.h"


PaddleObject::PaddleObject(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	m_Shape.setPosition(pos);
	m_Shape.setSize(size);
	m_Shape.setFillColor(color);
	m_Shape.setOrigin(size / 2.f);
}


PaddleObject::~PaddleObject()
{
}

void PaddleObject::UpdatePosition(sf::Time & deltaTime)
{
}


