#pragma once
#include <SFML/Graphics.hpp>

#include "Menu.h"

namespace Arkanoid
{
	class Game;

	class GameStatePauseMenuData
	{
	private:
		Menu* menu;
		sf::Font* font;
		sf::RectangleShape* background;
		sf::Text* titleText;
	public:
		GameStatePauseMenuData();
		~GameStatePauseMenuData();
		void Draw(sf::RenderWindow& window);
		void HandleWindowEvent(const sf::Event& event);
		void Init();
		void Update(float timeDelta);
	};
}
