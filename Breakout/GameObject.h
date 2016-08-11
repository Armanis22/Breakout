#pragma once
class GameObject
{
public:
	

	//virtual sf::Text GetText() = 0;
	//virtual sf::RectangleShape GetRectangle() { return m_Shape; }

	
protected:
	sf::Vector2f m_Position;
	sf::Color m_Color;
	sf::Vector2f m_Size;
	//sf::Text m_Text;
	sf::RectangleShape m_Shape;
};

