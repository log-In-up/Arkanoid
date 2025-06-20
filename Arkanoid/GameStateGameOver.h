#pragma once
#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	class Game;

	class GameStateGameOverData
	{
	private:
		float timeSinceGameOver = 0.f;

		// Resources
		sf::Font* font;

		// UI data
		sf::RectangleShape* background;
		sf::Text* gameOverText;
		sf::Text* hintText;
		std::vector<sf::Text>* recordsTableTexts;
	public:
		GameStateGameOverData();
		~GameStateGameOverData();
		void Draw(sf::RenderWindow& window);
		void HandleWindowEvent(const sf::Event& event);
		void Init();
		void Update(float timeDelta);
	};
}
