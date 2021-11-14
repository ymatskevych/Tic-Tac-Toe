#include "Renderer.h"

#include <iostream>
#include <Windows.h>

void Renderer::Tick(float InDeltaTime)
{
	Draw();

	// Add assert
	if (m_CurrentLevel)
	{
		m_CurrentLevel->ProcessInput();
	}

	StabilizeConsoleOutput();
}

void Renderer::Draw()
{
	// Add assert
	if (m_CurrentLevel)
	{
		std::cout << m_CurrentLevel->GetLevelAsString();
	}
}

void Renderer::StabilizeConsoleOutput()
{
	constexpr COORD CursorPosition {0, 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}
