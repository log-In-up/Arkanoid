#pragma once
#include <SFML/Graphics.hpp>

#include "Collidable.h"
#include "GameObject.h"

namespace Arkanoid
{
	class Platform : public GameObject, public Colladiable
	{
	public:
		Platform(const sf::Vector2f& position);

		bool CheckCollision(std::shared_ptr<Colladiable> collidable) override;
		bool GetCollision(std::shared_ptr<Colladiable> collidable) const override;
		void ChangeWidth(float multiplyWidth);
		void OnHit() override;
		void Update(float timeDelta) override;
	private:
		void Move(float speed);
	};
}