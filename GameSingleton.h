#pragma once

#include "InputController.h"
#include "LevelController.h"
#include "Field.h"

enum class EPlayerType
{
	ZERO,
	CROSS
};

class GameSingleton
{
public:

	void Initialize();

	const InputController& GetInputController() const { return m_InputController; }
	const LevelController& GetLevelController() const { return m_LevelController; }
	LevelController& GetLevelController() { return m_LevelController; }
	Field& GetField() { return m_Field; }
	EPlayerType GetPlayerType() const { return m_PlayerType; }
	EPlayerType GetAIPlayerType() const { return m_AIPlayerType; }

	EGameResult GetGameResult() const { return m_GameResult; }
	void SetGameResult(EGameResult InGameResult) { m_GameResult = InGameResult; }

	void SetPlayerType(EPlayerType InPlayerType);

private:

	InputController m_InputController;
	LevelController m_LevelController;
	Field m_Field;

	EGameResult m_GameResult = EGameResult::None;

	EPlayerType m_PlayerType = EPlayerType::CROSS;
	EPlayerType m_AIPlayerType = EPlayerType::ZERO;

// Singleton
public:
	
	static GameSingleton& Get()
	{
		return s_Instance;
	}
private:
	
	GameSingleton() = default;
	static GameSingleton s_Instance;
};
