// SFMLTemplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include "GlobalConsts.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Breakout!");
	window.setMouseCursorVisible(false);
	//window.setFramerateLimit(120);

	Game myGame;
	while (window.isOpen())
	{
		myGame.Update(window);
		myGame.Draw(window);
	}
	return 0;
}

