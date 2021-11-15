#pragma once

enum class Key
{
	None = -1,

	UP    = 72,
	DOWN  = 80,
	ENTER = 13,
	LEFT  = 75,
	RIGHT = 77, // to add 

	MAX
};

inline bool KeyExist(int32_t InKeyCode)
{
	const Key CastedKeyCode = static_cast<Key>(InKeyCode);

	switch (CastedKeyCode)
	{
	case Key::UP:
	case Key::DOWN:
	case Key::ENTER:
	case Key::LEFT:
	case Key::RIGHT:
		return true;

	default: return false;
	}
}