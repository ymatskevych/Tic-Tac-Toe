#include "Renderer.h"
#include "Ticker.h"

int main()
{
	Renderer renderer;
	Ticker ticker;
	ticker.AddTickable(&renderer);
	
	while (true)
	{
		ticker.Tick();
	}
}