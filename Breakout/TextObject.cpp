#include "stdafx.h"
#include "TextObject.h"


TextObject::TextObject(sf::String string, sf::Color color, sf::Vector2f pos, int charSize)
{
	if (!m_Font.loadFromFile("Media/consola.ttf"))
	{
		printf("Error Loading Font\n");
	}
	m_Text.setString(string);
	m_Text.setPosition(pos);
	m_Text.setColor(color);
	m_Text.setCharacterSize(charSize);
	m_Text.setFont(m_Font);
	
}

TextObject::~TextObject()
{
}
