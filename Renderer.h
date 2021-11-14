#pragma once

#include "Interfaces/ITickable.h"

class Renderer : public ITickable
{
public:

	void Tick(float InDeltaTime) override;

private:

	void Draw();

	void StabilizeConsoleOutput();
};
