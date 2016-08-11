#pragma once
#include "GameObject.h"
class TextObject :
	public GameObject
{
public:
	TextObject(sf::String string, sf::Color color, sf::Vector2f pos, int charSize);
	~TextObject();

	sf::Text GetText() { return m_Text; }


protected:
	sf::Font m_Font;
	sf::Text m_Text;

};

