#pragma once

#include "Interfaces/ITickable.h"
#include "Interfaces/ILevel.h"
#include "Datas/LevelData.h"

class Renderer : public ITickable
{
public:

	void Tick(float InDeltaTime) override;

private:

	void Draw();

	void StabilizeConsoleOutput();

	// TODO: Add level manager
	ILevel* m_CurrentLevel = new ChooseDimentionLevel;
};
