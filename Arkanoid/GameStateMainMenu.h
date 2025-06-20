#pragma once
#include <SFML/Graphics.hpp>

#include "Menu.h"

namespace Arkanoid
{
	class Game;

	class GameStateMainMenuData
	{
	private:
		sf::Font* font;
		Menu* menu;
	public:
		GameStateMainMenuData();
		~GameStateMainMenuData();
		void Draw(sf::RenderWindow& window);
		void HandleWindowEvent(const sf::Event& event);
		void Init();
		void Update(float timeDelta);
	};
}
