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

	SelectCell();
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
		FillCell(false);
		if (CheckForWinCross())
		{
			system("Pause");
		}

		GetBestMove()->FillCell(true);
		if (CheckForWinZero())
		{
			system("Pause");
		}
		break;
	}
	default: break;
	}

	SelectCell();
}

void Field::FillCell(bool IsZero)
{
	if (SelectedCell)
	{
		SelectedCell->FillCell(IsZero);
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

bool Field::CheckForWinCross()
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

bool Field::CheckForWinZero()
{
	// Check columns
	bool IsDiagonal = true;
	for (int32_t x = 0; x < m_DimentionAmount; ++x)
	{
		bool IsRowWinner = true;
		for (int32_t y = 0; y < m_DimentionAmount; ++y)
		{
			if (!GetCell(x, y)->IsZero() || GetCell(x, y)->IsEmpty())
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
			if (!GetCell(x, y)->IsZero() || GetCell(x, y)->IsEmpty())
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

bool Field::CheckForDraw()
{
	for (int32_t x = 0; x < m_DimentionAmount; ++x)
	{
		for (int32_t y = 0; y < m_DimentionAmount; ++y)
		{
			if (GetCell(x, y)->IsEmpty())
			{
				return false;
			}
		}
	}
	return true;
}

int32_t Field::Minimax(Field* CopyField, int32_t depth, bool IsMaximazing)
{
	if (CopyField->CheckForWinZero())
	{
		return 1;
	}
	if (CopyField->CheckForWinCross())
	{
		return -1;
	}
	if (CopyField->CheckForDraw())
	{
		return 0;
	}

	if (IsMaximazing)
	{
		int32_t BestScore = IsMaximazing ? -10000 : 10000;
		for (int32_t x = 0; x < m_DimentionAmount; ++x)
		{
			for (int32_t y = 0; y < m_DimentionAmount; ++y)
			{
				if (CopyField->GetCell(x, y)->IsEmpty())
				{
					CopyField->GetCell(x, y)->SetZero();
					BestScore = std::max(BestScore, CopyField->Minimax(CopyField, depth + 1, false));
					//CopyField->GetCell(x, y)->SetEmpty();
				}
			}
		}
		return BestScore;
	}
	else
	{
		int32_t BestScore = 10000;
		for (int32_t x = 0; x < m_DimentionAmount; ++x)
		{
			for (int32_t y = 0; y < m_DimentionAmount; ++y)
			{
				if (CopyField->GetCell(x, y)->IsEmpty())
				{
					CopyField->GetCell(x, y)->SetCross();
					BestScore = std::min(BestScore, CopyField->Minimax(CopyField, depth + 1, true));
					//CopyField->GetCell(x, y)->SetEmpty();
				}
			}
		}
		return BestScore;
	}
}

FieldCell* Field::GetBestMove()
{
	int32_t BestScore = -100000;
	FieldCell* BestCell = nullptr;

	for (int32_t x = 0; x < m_DimentionAmount; ++x)
	{
		for (int32_t y = 0; y < m_DimentionAmount; ++y)
		{
			if (GetCell(x, y)->IsEmpty())
			{
				Field Copy = *this;
				Copy.GetCell(x, y)->SetZero();
				const int32_t Score = Minimax(&Copy, 0, false);
				//GetCell(x, y)->SetEmpty();

				if (Score > BestScore)
				{
					BestScore = Score;
					BestCell = GetCell(x, y);
				}
			}
		}
	}

	return BestCell;
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
