#pragma once

class ITickable
{
public:

	virtual void Tick(float InDeltaTime) = 0;
};
