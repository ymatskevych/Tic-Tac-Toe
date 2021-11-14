#pragma once

#include "Interfaces/ITickable.h"

#include <ctime>
#include <vector>

class Ticker
{
public:

	void Tick();

	void AddTickable(ITickable* InTickable);

private:

	std::vector<ITickable*> m_Tickables;
	float m_DeltaTime = 0.f;

	float Time = static_cast<float>(clock());
};
