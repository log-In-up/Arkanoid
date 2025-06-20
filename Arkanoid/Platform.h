#pragma once
#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	class Ball;

	class Platform
	{
	private:
		sf::Sprite* sprite;
		sf::Texture* texture;
	public:
		sf::FloatRect GetRect() const
		{
			return sprite->getGlobalBounds();
		}
	public:
		Platform();
		~Platform();
		bool CheckCollisionWithBall(const Ball& ball);
		void Draw(sf::RenderWindow& window) const;
		void Init();
		void Update(float timeDelta);
	private:
		void Move(float speed);
	};
}