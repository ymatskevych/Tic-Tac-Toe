#pragma once

enum class Key
{
	None = -1,

	UP    = 72,
	DOWN  = 80,
	ENTER = 13,

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
		return true;

	default: return false;
	}
}