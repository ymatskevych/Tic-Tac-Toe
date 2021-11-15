#include "Field.h"

#include <conio.h>

#include "GameSingleton.h"

void Field::GenerateCells()
{
	for (int32_t x = 0; x <= m_DimentionAmount; ++x)
	{
		for (int32_t y = 0; y <= m_DimentionAmount; ++y)
		{
			m_Cells.push_back(FieldCell(x, y));
		}
	}
}

void Field::Tick(float InDeltaTime)
{
	if (_kbhit())
	{
		ProcessInput();
	}
}

void Field::ProcessInput()
{
	const Key Input = GameSingleton::Get().GetInputController().GetLastInput();
	switch (Input)
	{
	case Key::UP:
	{
		m_YCursor = std::max(0, m_YCursor - 1);
		break;
	}
	case Key::DOWN:
	{
		m_YCursor = std::min(m_DimentionAmount - 1, m_YCursor + 1);
		break;
	}
	case Key::LEFT:
	{
		m_XCursor = std::max(0, m_XCursor - 1);
		break;
	}
	case Key::RIGHT:
	{
		m_XCursor = std::min(m_DimentionAmount - 1, m_XCursor + 1);
		break;
	}
	case Key::ENTER:
	{
		FillCell();
		if (CheckForWin())
		{
			system("Pause");
		}
		break;
	}
	default: break;
	}

	SelectCell();
}

void Field::FillCell()
{
	if (SelectedCell)
	{
		SelectedCell->FillCell();
	}
}

void Field::SelectCell()
{
	if (SelectedCell)
	{
		SelectedCell->UnSelect();
	}

	SelectedCell = GetCell(m_YCursor, m_XCursor);
	SelectedCell->SetSelected();
}

bool Field::CheckForWin()
{
	// Check columns
	bool IsDiagonal = true;
	for (int32_t x = 0; x < m_DimentionAmount; ++x)
	{
		bool IsRowWinner = true;
		for (int32_t y = 0; y < m_DimentionAmount; ++y)
		{
			if (!GetCell(x, y)->IsCross() || GetCell(x, y)->IsEmpty())
			{
				if (x == y)
				{
					IsDiagonal = false;
				}
				IsRowWinner = false;
			}
		}
		if (IsRowWinner)
		{
			return true;
		}
	}
	if (IsDiagonal)
	{
		return true;
	}

	// Check rows
	IsDiagonal = true;
	for (int32_t y = 0; y < m_DimentionAmount; ++y)
	{
		bool IsRowWinner = true;
		for (int32_t x = 0; x < m_DimentionAmount; ++x)
		{
			if (!GetCell(x, y)->IsCross() || GetCell(x, y)->IsEmpty())
			{
				if (x + y == m_DimentionAmount - 1)
				{
					IsDiagonal = false;
				}
				IsRowWinner = false;
			}
		}
		if (IsRowWinner)
		{
			return true;
		}
	}
	if (IsDiagonal)
	{
		return true;
	}

	return false;
}

std::string Field::GetFieldAsString()
{
	std::string FieldDraw;

	const int32_t DimentionIndex = m_DimentionAmount * 2;
	for (int32_t i = 1; i < DimentionIndex; ++i)
	{
		for (int32_t j = 1; j < DimentionIndex; ++j)
		{
			if (i % 2 == 0)
			{
				FieldDraw += "-";
			}
			else
			{
				// x = (i - 1) / 2; y = j / 2
				FieldDraw += j % 2 == 0 ? "|" : GetCell((i - 1) / 2, j / 2)->GetSymbol();
			}
		}
		FieldDraw += "\n";
	}
	return FieldDraw;
}

FieldCell* Field::GetCell(int32_t InX, int32_t InY)
{
	const int32_t CellIndex = (InX + 1) + m_DimentionAmount * InY;
	return &m_Cells.at(CellIndex);
}
