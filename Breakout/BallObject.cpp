#include "stdafx.h"
#include "BallObject.h"



BallObject::BallObject(sf::Vector2f pos, float radius, sf::Color color)
{
	m_BallShape.setPosition(pos);
	m_BallShape.setRadius(radius);
	m_BallShape.setFillColor(color);
	m_BallShape.setOrigin(sf::Vector2f(radius/2.f,radius/2.f));
}

BallObject::~BallObject()
{
}

void BallObject::UpdatePosition(sf::Time& deltaTime)
{
	m_BallShape.move(m_Velocity * deltaTime.asSeconds());
}

void BallObject::UpdatePosition(Collider& collider)
{
	//reverse velocities and add a little bit of pushout
	//right and bottom needed more pushout. collision issues causing ball to get stuck inside
	if (collider.GetContactLeft() || collider.GetContactRight())
	{ 
		if (collider.GetContactRight())
			m_BallShape.move(-6, 0);
		else
			m_BallShape.move(1, 0);
		m_Velocity.x *= -1;
	}
	if (collider.GetContactTop() || collider.GetContactBottom())
	{
		if (collider.GetContactBottom())
			m_BallShape.move(0, -6);
		else
			m_BallShape.move(0, 1);
		m_Velocity.y *= -1;
	}
}
void BallObject::UpdatePosition(sf::Vector2i mousePos)
{
	mousePos.y = 628;
	m_Velocity = sf::Vector2f(300, -300);
	m_BallShape.setPosition(static_cast<sf::Vector2f>(mousePos));
	if (m_BallShape.getPosition().x < 100)
		m_BallShape.setPosition(100, mousePos.y);
	if (m_BallShape.getPosition().x > 1100)
		m_BallShape.setPosition(1100, mousePos.y);
}

void BallObject::PaddleHit(sf::Vector2f paddlePos)
{
	double _magnitude = sqrtf((m_Velocity.x * m_Velocity.x) + (m_Velocity.y * m_Velocity.y));
	float _differenceX = m_BallShape.getPosition().x - paddlePos.x;
	// get normalized by dividing the difference between half the paddle length
	float _normalized = _differenceX / 80;
	//multiply normalized by the max angle to get new angle
	float _newAngle = _normalized * 75;
	//minimum angle set to 15 degrees
	if (_newAngle > -15 && _newAngle < 15)
	{
		if (_newAngle < 0)
			_newAngle = -15;
		else
			_newAngle = 15;
	}
	//trig from angle to get new x,y values
	//finally worked when i changed the angle to radians in the parenthesis
	float _newY = cosf(_newAngle * PI / 180) * _magnitude;
	float _newX = sinf(_newAngle * PI / 180) * _magnitude;
	
	m_Velocity = sf::Vector2f(_newX,_newY * -1);
	m_BallShape.move(0, -5);
	m_Velocity.x *= 1.01;
	m_Velocity.y *= 1.01;
}

