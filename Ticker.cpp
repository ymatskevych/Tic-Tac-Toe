#include "Ticker.h"
#include <windows.h>

void Ticker::Tick()
{
	if ((static_cast<float>(clock()) - Time) / CLOCKS_PER_SEC >= 0.1f)
	{
		for (ITickable* Tickable : m_Tickables)
		{
			// Add assert
			if (Tickable)
			{
				Tickable->Tick(m_DeltaTime);
			}
		}
		Time = static_cast<float>(clock());
	}

	const HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	// Add assert
	if (Handle)
	{
		SetConsoleCursorPosition(Handle, { 0,0 });
	}
}

void Ticker::AddTickable(ITickable* InTickable)
{
	// Add assert
	m_Tickables.push_back(InTickable);
}
