#include "LevelController.h"
#include "Tools.h"

void LevelController::GoToNextLevel()
{
	system("CLS");

	if (!VectorTools::Contains(Levels, m_CurrentLevelIndex + 1))
	{
		// assert
		return;
	}
	m_CurrentLevelIndex++;
}

ILevel* LevelController::GetCurrentLevel() const
{
	if (!VectorTools::Contains(Levels, m_CurrentLevelIndex))
	{
		// assert
		return nullptr;
	}
	return Levels.at(m_CurrentLevelIndex);
}

void LevelController::AddLevel(ILevel* InLevel)
{
	// assert
	Levels.push_back(InLevel);
}
