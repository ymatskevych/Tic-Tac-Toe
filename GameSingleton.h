#pragma once

#include "InputController.h"

class GameSingleton
{
public:

	const InputController& GetInputController() const { return m_InputController; }

private:

	InputController m_InputController;

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