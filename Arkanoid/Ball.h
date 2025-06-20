#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace Arkanoid
{
	class Ball
	{
	private:
		sf::Sprite* sprite;
		sf::Texture* texture;
		sf::Vector2f* direction;
	public:
		const sf::Vector2f& GetPosition() const
		{
			return sprite->getPosition();
		}
	public:
		Ball();
		~Ball();
		void Draw(sf::RenderWindow& window) const;
		void Init();
		void ReboundFromPlatform();
		void Update(float timeDelta);
	};
}
