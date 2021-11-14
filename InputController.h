#pragma once

#include <cstdint>
#include "Datas/KeyboardData.h"

class InputController
{
public:

	Key GetLastInput() const;

private:

	Key ConvertKeyCode(int32_t InKeyCode) const;
};