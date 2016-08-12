#pragma once
class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual sf::Text GetText() { return m_Text; }
	virtual sf::RectangleShape GetRectangle() {	return m_Shape;}
	virtual sf::CircleShape GetBall() { return m_BallShape; }
	virtual void UpdatePosition(sf::Time& deltaTime) 
	{
		m_Velocity += m_NewVelocity;
		m_BallShape.move(m_Velocity * deltaTime.asSeconds());
	}
	
protected:
	sf::Vector2f m_NewVelocity;
	sf::Color m_Color;
	sf::Vector2f m_Size;
	sf::Text m_Text;
	sf::RectangleShape m_Shape;
	sf::CircleShape m_BallShape;
	sf::Vector2f m_Velocity;
};

