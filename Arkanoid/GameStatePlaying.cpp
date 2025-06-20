#include <assert.h>
#include <sstream>

#include "Application.h"
#include "Game.h"
#include "GameStatePlaying.h"
#include "Text.h"

namespace Arkanoid
{
	GameStatePlayingData::GameStatePlayingData()
	{
		font = new sf::Font();
		eatAppleSoundBuffer = new sf::SoundBuffer();
		gameOverSoundBuffer = new sf::SoundBuffer();
		appleTexture = new sf::Texture();
		rockTexture = new sf::Texture();

		ball = new Ball();
		platform = new Platform();

		background = new sf::RectangleShape();
		inputHintText = new sf::Text();
		scoreText = new sf::Text();

		gameOverSound = new sf::Sound();
	}

	GameStatePlayingData::~GameStatePlayingData()
	{
		delete font;
		delete eatAppleSoundBuffer;
		delete gameOverSoundBuffer;
		delete appleTexture;
		delete rockTexture;
		delete ball;
		delete platform;
		delete background;
		delete inputHintText;
		delete scoreText;
		delete gameOverSound;
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(*background);

		// Draw game objects
		platform->Draw(window);
		ball->Draw(window);

		scoreText->setOrigin(GetTextOrigin(*scoreText, { 0.f, 0.f }));
		scoreText->setPosition(10.f, 10.f);
		window.draw(*scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText->setPosition(viewSize.x - 10.f, 10.f);
		window.draw(*inputHintText);
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::Init()
	{
		// Init game resources (terminate if error)
		assert(font->loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer->loadFromFile(SOUNDS_PATH + "Death.wav"));

		// Init background
		background->setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background->setPosition(0.f, 0.f);
		background->setFillColor(sf::Color(0, 0, 0));

		scoreText->setFont(*font);
		scoreText->setCharacterSize(24);
		scoreText->setFillColor(sf::Color::Yellow);

		SetTextData(*inputHintText, "Use arrow keys to move, ESC to pause", *font, 24, sf::Color::White);
		inputHintText->setOrigin(GetTextOrigin(*inputHintText, { 1.f, 0.f }));

		platform->Init();
		ball->Init();

		// Init sounds
		gameOverSound->setBuffer(*gameOverSoundBuffer);
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		platform->Update(timeDelta);
		ball->Update(timeDelta);

		const bool isCollision = platform->CheckCollisionWithBall(*ball);
		if (isCollision)
		{
			ball->ReboundFromPlatform();
		}

		const bool isGameFinished = !isCollision && ball->GetPosition().y > platform->GetRect().top;

		if (isGameFinished)
		{
			gameOverSound->play();

			Game& game = Application::Instance().GetGame();

			game.PushState(GameStateType::GameOver, false);
		}
	}
}