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
	//m_Velocity = m_NewVelocity;
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
			m_BallShape.move(0, -14);
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

void BallObject::PaddleHit(sf::Vector2f paddlePos)
{
	//get the different between the ball origin and paddle origin
	//calculate new vector based off of old vecter and the difference of the positions
	
	m_Velocity *= 1.01f;
	//m_BallShape.move(0, -3);
	float _intersectX = m_BallShape.getPosition().x - paddlePos.x;
	
	//this kinda works might come back to it
	double _magnitude = sqrt((m_Velocity.x * m_Velocity.x) + (m_Velocity.y * m_Velocity.y));
	//float _newX = cos(_intersectX) * _magnitude;
	//float _newY = sin(_intersectX) * _magnitude;
	//printf("mag %f\n", _intersectX);
	//m_Velocity = sf::Vector2f(_newX, _newY);

	// normalize the intersect point
	float _normalizedAngle = _intersectX / 80;
	//get the new angle by multiplying by the max angle i want of 65
	float _newAngle = _normalizedAngle * 45;
	float _newX = cos(abs(_newAngle)) * _magnitude;
	float _newY = sin(abs(_newAngle)) * _magnitude;
	m_Velocity = sf::Vector2f(_newX, _newY);
	//printf("mag %f\n", _normalizedAngle);

}

