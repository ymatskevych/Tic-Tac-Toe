#pragma once
#include <vector>


class ILevel;

class LevelController
{
public:

	void GoToNextLevel();

	ILevel* GetCurrentLevel() const;
	void AddLevel(ILevel* InLevel);

private:

	int32_t m_CurrentLevelIndex = 0;
	std::vector<ILevel*> Levels;
};
