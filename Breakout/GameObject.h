#pragma once
class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual sf::Text GetText() { return m_Text; }
	virtual sf::RectangleShape GetRectangle() {	return m_Shape;}
	virtual sf::CircleShape GetBall() { return m_BallShape; }
	//tried using just the one update position for ball and paddle here. wouldnt work
	virtual void UpdatePosition(sf::Time& deltaTime) {}
	
protected:
	sf::Vector2f m_NewVelocity;
	sf::Color m_Color;
	sf::Vector2f m_Size;
	sf::Text m_Text;
	sf::RectangleShape m_Shape;
	sf::CircleShape m_BallShape;
	sf::Vector2f m_Velocity;
};

