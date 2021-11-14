#pragma once

#include <string>

class ILevel
{
public:

	virtual std::string GetLevelAsString() const = 0;
	virtual void ProcessInput() = 0;
};
