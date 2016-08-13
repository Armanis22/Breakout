#include "stdafx.h"
#include "BallObject.h"



BallObject::BallObject(sf::Vector2f pos, float radius, sf::Color color)
{
	m_BallShape.setPosition(pos);
	m_BallShape.setRadius(radius);
	m_BallShape.setFillColor(color);
	m_BallShape.setOrigin(sf::Vector2f(radius/2.f,radius/2.f));
	m_Velocity = sf::Vector2f(-200, -100);
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
		m_Velocity.x *= -1;
	}
	if (collider.GetContactTop() || collider.GetContactBottom())
	{
		m_Velocity.y *= -1;
	}
	if (collider.GetContactBottom())
	{
		m_Velocity += sf::Vector2f(2, 2);
	}
}

