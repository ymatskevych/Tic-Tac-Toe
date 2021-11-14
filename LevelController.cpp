#include "LevelController.h"
#include "Tools.h"

void LevelController::GoToNextLevel()
{
	system("CLS");

	if (!VectorTools::Contains(Levels, m_CurrentLevelIndex + 1))
	{
		_STL_REPORT_ERROR("[LevelController]: Levels does not contain level at m_CurrentLevelIndex");
		return;
	}
	m_CurrentLevelIndex++;
}

ILevel* LevelController::GetCurrentLevel() const
{
	if (!VectorTools::Contains(Levels, m_CurrentLevelIndex))
	{
		_STL_REPORT_ERROR("[LevelController]: Levels does not contain level at m_CurrentLevelIndex");
		return nullptr;
	}
	return Levels.at(m_CurrentLevelIndex);
}

void LevelController::AddLevel(ILevel* InLevel)
{
	_STL_VERIFY(InLevel, "[LevelController]: InLevel is nullptr");
	Levels.push_back(InLevel);
}
