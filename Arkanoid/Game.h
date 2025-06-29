#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "GameSettings.h"
#include "GameState.h"
#include "Sprite.h"

namespace Arkanoid
{
	enum class GameOptions : std::uint8_t
	{
		InfiniteApples = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteApples | WithAcceleration,
		Empty = 0
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	class Game
	{
	private:
		using RecordsTable = std::unordered_map<std::string, int>;

		std::vector<GameState>* stateStack;

		GameStateChangeType stateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		GameOptions options = GameOptions::Default;

		RecordsTable* recordsTable;

		bool pendingGameStateIsExclusivelyVisible = false;
	public:
		const RecordsTable& GetRecordsTable() const
		{
			return *recordsTable;
		}
	public:
		Game();
		~Game();
		bool IsEnableOptions(GameOptions option) const;
		int GetRecordByPlayerId(const std::string& playerId) const;
		void ExitGame();
		void LoadNextLevel();
		void LooseGame();
		void PauseGame();
		void PopState(); // Remove current game state from the stack
		void QuitGame();
		void SetOption(GameOptions option, bool value);
		void ShowRecords();
		void StartGame();
		void UpdateGame(float timeDelta, sf::RenderWindow& window);
		void WinGame();
	private:
		bool Update(float timeDelta); // Return false if game should be closed
		void Draw(sf::RenderWindow& window);
		void HandleWindowEvents(sf::RenderWindow& window);
		void PushState(GameStateType stateType, bool isExclusivelyVisible); // Add new game state on top of the stack
		void Shutdown();
		void SwitchStateTo(GameStateType newState); // Remove all game states from the stack and add new one
		void UpdateRecord(const std::string& playerId, int score);
	};
}
