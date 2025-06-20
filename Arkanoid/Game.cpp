#include <algorithm>
#include <assert.h>

#include "Game.h"
#include "GameStateGameOver.h"
#include "GameStateMainMenu.h"
#include "GameStatePauseMenu.h"
#include "GameStatePlaying.h"
#include "GameStateRecords.h"

namespace Arkanoid
{
	Game::Game()
	{
		stateStack = new std::vector<GameState>();

		// Generate fake records table
		recordsTable = new RecordsTable();
		recordsTable->insert({ "John", MAX_APPLES / 2 });
		recordsTable->insert({ "Jane", MAX_APPLES / 3 });
		recordsTable->insert({ "Alice", MAX_APPLES / 4 });
		recordsTable->insert({ "Bob", MAX_APPLES / 5 });
		recordsTable->insert({ "Clementine", MAX_APPLES / 5 });

		//recordsTable =
		//{
		//	{"John", MAX_APPLES / 2},
		//	{"Jane", MAX_APPLES / 3 },
		//	{"Alice", MAX_APPLES / 4 },
		//	{"Bob", MAX_APPLES / 5 },
		//	{"Clementine", MAX_APPLES / 5 },
		//};

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = new bool(false);
		SwitchStateTo(GameStateType::MainMenu);
	}

	Game::~Game()
	{
		stateStack->clear();
		delete stateStack;

		recordsTable->clear();
		delete recordsTable;

		delete pendingGameStateIsExclusivelyVisible;

		Shutdown();
	}

	bool Game::IsEnableOptions(GameOptions option) const
	{
		const bool isEnable = ((std::uint8_t)options & (std::uint8_t)option) != (std::uint8_t)GameOptions::Empty;
		return isEnable;
	}

	bool Game::Update(float timeDelta)
	{
		if (stateChangeType == GameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (stateStack->size() > 0)
			{
				stateStack->pop_back();
			}
		}
		else if (stateChangeType == GameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (stateStack->size() > 0)
			{
				stateStack->pop_back();
			}
		}

		// Initialize new game state if needed
		if (pendingGameStateType != GameStateType::None)
		{
			stateStack->push_back(GameState(pendingGameStateType, pendingGameStateIsExclusivelyVisible));
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		*pendingGameStateIsExclusivelyVisible = false;

		if (stateStack->size() > 0)
		{
			stateStack->back().Update(timeDelta);
			return true;
		}

		return false;
	}

	int Game::GetRecordByPlayerId(const std::string& playerId) const
	{
		auto it = recordsTable->find(playerId);
		return it == recordsTable->end() ? 0 : it->second;
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (stateStack->size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = stateStack->rbegin(); it != stateStack->rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->IsExclusivelyVisible())
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				(*it)->Draw(window);
			}
		}
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (stateStack->size() > 0)
			{
				stateStack->back().HandleWindowEvent(event);
			}
		}
	}

	void Game::PopState()
	{
		pendingGameStateType = GameStateType::None;
		*pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Pop;
	}

	void Game::PushState(GameStateType stateType, bool isExclusivelyVisible)
	{
		pendingGameStateType = stateType;
		*pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		stateChangeType = GameStateChangeType::Push;
	}

	void Game::SetOption(GameOptions option, bool value)
	{
		if (value) {
			options = (GameOptions)((std::uint8_t)options | (std::uint8_t)option);
		}
		else {
			options = (GameOptions)((std::uint8_t)options & ~(std::uint8_t)option);
		}
	}

	void Game::Shutdown()
	{
		// Shutdown all game states
		while (stateStack->size() > 0)
		{
			stateStack->pop_back();
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		*pendingGameStateIsExclusivelyVisible = false;
	}

	void Game::SwitchStateTo(GameStateType newState)
	{
		pendingGameStateType = newState;
		*pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Switch;
	}

	void Game::UpdateRecord(const std::string& playerId, int score)
	{
		recordsTable->at(playerId) = std::max(recordsTable->at(playerId), score);
	}
}