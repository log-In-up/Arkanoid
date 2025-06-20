#pragma once
#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		ExitDialog,
		Records,
	};

	class GameState
	{
	private:
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	public:
		GameState(GameState&& state) noexcept
		{
			operator=(std::move(state));
		}

		template<class T>
		T* GetData() const {
			return static_cast<T>(data);
		}

		GameStateType GetType() const
		{
			return type;
		}

		bool IsExclusivelyVisible() const
		{
			return isExclusivelyVisible;
		}

		GameState& operator= (GameState&& state) noexcept
		{
			type = state.type;
			data = state.data;
			isExclusivelyVisible = state.isExclusivelyVisible;
			state.data = nullptr;
			return *this;
		}
	public:
		GameState() = default;
		GameState(const GameState& state) = delete;
		GameState(GameStateType type, bool isExclusivelyVisible);
		~GameState();

		GameState& operator= (const GameState& state) = delete;
		void Draw(sf::RenderWindow& window);
		void HandleWindowEvent(sf::Event& event);
		void Update(float timeDelta);
	private:
		void* CopyData(const GameState& state) const;
	};
}