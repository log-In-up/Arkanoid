#include <cstdlib>

#include "Application.h"

namespace Arkanoid
{
	Application& Application::Instance()
	{
		static Application instance;
		return instance;
	}

	void Application::Run()
	{
		sf::Clock gameClock;

		while (window->isOpen())
		{
			float startTime = gameClock.getElapsedTime().asSeconds();

			if (!window->isOpen())
			{
				break;
			}
			game->UpdateGame(SETTINGS.TIME_PER_FRAME, *window);

			float endTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = endTime - startTime;

			if (deltaTime < SETTINGS.TIME_PER_FRAME)
			{
				sf::sleep(sf::seconds(SETTINGS.TIME_PER_FRAME - deltaTime));
			}
		}
	}

	Application::Application()
	{
		window = new sf::RenderWindow(sf::VideoMode(SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEIGHT), SETTINGS.GAME_NAME);
		game = new Game();

		unsigned int seed = (unsigned int)time(nullptr);
		srand(seed);
	}

	Application::~Application()
	{
		delete window;
		delete game;
	}
}