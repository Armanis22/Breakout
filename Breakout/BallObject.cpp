#include "stdafx.h"
#include "BallObject.h"



BallObject::BallObject(sf::Vector2f pos, float radius, sf::Color color)
{
	m_BallShape.setPosition(pos);
	m_BallShape.setRadius(radius);
	m_BallShape.setFillColor(color);
	m_BallShape.setOrigin(sf::Vector2f(radius/2.f,radius/2.f));
	m_Velocity = sf::Vector2f(200, -200);
}

BallObject::~BallObject()
{
}

void BallObject::UpdatePosition(sf::Time& deltaTime)
{
	m_Velocity += m_NewVelocity;
	m_BallShape.move(m_Velocity * deltaTime.asSeconds());
}

void BallObject::UpdatePosition(Collider& collider)
{
	if (collider.GetContactLeft() || collider.GetContactRight())
	{
		if (collider.GetContactRight())
			m_BallShape.move(-4, 0);
		m_Velocity.x *= -1;
	}
	if (collider.GetContactTop() || collider.GetContactBottom())
	{
		if (collider.GetContactBottom())
			m_BallShape.move(0, -4);
		m_Velocity.y *= -1;
	}
}

void BallObject::UpdatePosition(sf::Vector2i mousePos)
{
	mousePos.y = m_BallShape.getPosition().y;
	m_BallShape.setPosition(static_cast<sf::Vector2f>(mousePos));
	if (m_BallShape.getPosition().x < 100)
		m_BallShape.setPosition(100, mousePos.y);
	if (m_BallShape.getPosition().x > 1100)
		m_BallShape.setPosition(1100, mousePos.y);
}

