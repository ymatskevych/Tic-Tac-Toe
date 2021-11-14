#include "Ticker.h"
#include <windows.h>

void Ticker::Tick()
{
	if ((static_cast<float>(clock()) - Time) / CLOCKS_PER_SEC >= 0.1f)
	{
		for (ITickable* Tickable : m_Tickables)
		{
			_STL_VERIFY(Tickable, "[Ticker]: Tickable is nullptr");

			Tickable->Tick(m_DeltaTime);
		}
		Time = static_cast<float>(clock());
	}

	const HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	_STL_VERIFY(Handle, "[Ticker]: Handle is nullptr");
	SetConsoleCursorPosition(Handle, { 0,0 });
}

void Ticker::AddTickable(ITickable* InTickable)
{
	_STL_VERIFY(InTickable, "[Ticker]: InTickable is nullptr");
	m_Tickables.push_back(InTickable);
}
