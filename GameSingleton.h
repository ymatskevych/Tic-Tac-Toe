#pragma once

#include "InputController.h"
#include "LevelController.h"

class GameSingleton
{
public:

	void Initialize();

	const InputController& GetInputController() const { return m_InputController; }
	const LevelController& GetLevelController() const { return m_LevelController; }
	LevelController& GetLevelController() { return m_LevelController; }

private:

	InputController m_InputController;
	LevelController m_LevelController;

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
