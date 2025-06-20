#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace Arkanoid
{
	class Game;

	class GameStateRecordsData
	{
	private:
		// Resources
		sf::Font* font;

		sf::Text* hintText;
		sf::Text* titleText;
		std::vector<sf::Text>* tableTexts;
	public:
		GameStateRecordsData();
		~GameStateRecordsData();
		void Draw(sf::RenderWindow& window);
		void HandleWindowEvent(const sf::Event& event);
		void Init();
		void Update(float timeDelta);
	};
}
