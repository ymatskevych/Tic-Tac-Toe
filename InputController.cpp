#include "InputController.h"

#include <conio.h>

Key InputController::GetLastInput() const
{
	return ConvertKeyCode(_getch());
}

Key InputController::ConvertKeyCode(int32_t InKeyCode) const
{
	/*
	 * Calling _getch() when InKetCode equals to 224 is necessary
	 * because arrow inputs are operation inputs and return firstly 224 code
	 * then theirs code
	 */
	if (InKeyCode == 224)
	{
		InKeyCode = _getch();
	}

	return KeyExist(InKeyCode) ? static_cast<Key>(InKeyCode) : Key::None;
}
