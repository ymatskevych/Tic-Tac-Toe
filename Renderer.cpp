#include "Renderer.h"

#include <iostream>
#include <Windows.h>

#include "GameSingleton.h"
#include "Interfaces/ILevel.h"

void Renderer::Tick(float InDeltaTime)
{
	Draw();

	ILevel* CurrentLevel = GameSingleton::Get().GetLevelController().GetCurrentLevel();
	_STL_VERIFY(CurrentLevel, "[Renderer]: CurrentLevel is nullptr");
	CurrentLevel->ProcessInput();

	StabilizeConsoleOutput();
}

void Renderer::Draw()
{
	ILevel* CurrentLevel = GameSingleton::Get().GetLevelController().GetCurrentLevel();
	_STL_VERIFY(CurrentLevel, "[Renderer]: CurrentLevel is nullptr");
	std::cout << CurrentLevel->GetLevelAsString();
}

void Renderer::StabilizeConsoleOutput()
{
	constexpr COORD CursorPosition {0, 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}
