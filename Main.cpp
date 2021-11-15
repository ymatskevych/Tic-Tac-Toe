#include "GameSingleton.h"
#include "Renderer.h"
#include "Ticker.h"

int main()
{
	GameSingleton::Get().Initialize();

	Renderer renderer;
	Ticker ticker;
	ticker.AddTickable(&renderer);
	ticker.AddTickable(&GameSingleton::Get().GetField());
	
	while (true)
	{
		ticker.Tick();
	}
}