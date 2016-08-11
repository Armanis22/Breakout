// SFMLTemplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 750), "Breakout!");

	Game myGame;
	while (window.isOpen())
	{
		myGame.Update(window);
		myGame.Draw(window);
	}
	return 0;
}

