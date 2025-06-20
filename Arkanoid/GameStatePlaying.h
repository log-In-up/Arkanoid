#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Ball.h"
#include "Platform.h"

namespace Arkanoid
{
	class Game;

	class GameStatePlayingData
	{
	private:
		// Resources
		sf::Font* font;
		sf::SoundBuffer* eatAppleSoundBuffer;
		sf::SoundBuffer* gameOverSoundBuffer;
		sf::Texture* appleTexture;
		sf::Texture* rockTexture;

		// Game data
		Ball* ball;
		Platform* platform;

		// UI data
		sf::RectangleShape* background;
		sf::Text* inputHintText;
		sf::Text* scoreText;

		// Sounds
		sf::Sound* gameOverSound;
	public:
		GameStatePlayingData();
		~GameStatePlayingData();
		void Draw(sf::RenderWindow& window);
		void HandleWindowEvent(const sf::Event& event);
		void Init();
		void Update(float timeDelta);
	};
}
