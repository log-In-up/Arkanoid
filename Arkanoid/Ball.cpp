#include <assert.h>

#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"

namespace
{
	// id textures
	const std::string TEXTURE_ID = "ball";
}

namespace Arkanoid
{
	Ball::Ball()
	{
		sprite = new sf::Sprite();
		texture = new sf::Texture();
		direction = new sf::Vector2f();
	}

	Ball::~Ball()
	{
		delete sprite;
		delete direction;
		delete texture;
	}

	void Ball::Draw(sf::RenderWindow& window) const
	{
		DrawSprite(*sprite, window);
	}

	void Ball::Init()
	{
		assert(texture->loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));

		InitSprite(*sprite, BALL_SIZE, BALL_SIZE, *texture);
		sprite->setPosition({ SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - PLATFORM_HEIGHT - BALL_SIZE / 2.f });

		const float angle = 45.f + rand() % 90; // [45, 135] degree
		const auto pi = std::acos(-1.f);
		direction->x = std::cos(pi / 180.f * angle);
		direction->y = std::sin(pi / 180.f * angle);
	}

	void Ball::ReboundFromPlatform()
	{
		direction->y *= -1;
	}

	void Ball::Update(float timeDelta)
	{
		const auto pos = sprite->getPosition() + BALL_SPEED * timeDelta * *direction;
		sprite->setPosition(pos);

		if (pos.x <= 0 || pos.x >= SCREEN_WIDTH)
		{
			direction->x *= -1;
		}

		if (pos.y <= 0 || pos.y >= SCREEN_HEIGHT)
		{
			direction->y *= -1;
		}
	}
}