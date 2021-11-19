#include "Field.h"

#include <conio.h>

#include "FieldCell.h"
#include "GameSingleton.h"

void Field::GenerateCells()
{
	for (int32_t x = 0; x <= m_DimentionAmount; ++x)
	{
		for (int32_t y = 0; y <= m_DimentionAmount; ++y)
		{
			FieldCell FieldCell;
			m_Cells.emplace_back(FieldCell);
		}
	}
}

void Field::Initialize()
{
	GenerateCells();

	if (GameSingleton::Get().GetAIPlayerType() == ETokenType::CROSS)
	{
		GetBestMove()->SetToken(GameSingleton::Get().GetAIPlayerType());
	}

	SelectStartCell();
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
		m_XCursor = std::max(0, m_XCursor - 1);
		break;
	}
	case Key::DOWN:
	{
		m_XCursor = std::min(m_DimentionAmount - 1, m_XCursor + 1);
		break;
	}
	case Key::LEFT:
	{
		m_YCursor = std::max(0, m_YCursor - 1);
		break;
	}
	case Key::RIGHT:
	{
		m_YCursor = std::min(m_DimentionAmount - 1, m_YCursor + 1);
		break;
	}
	case Key::ENTER:
	{
		if (!IsSelectionEmpty())
		{
			break;
		}

		FillCell(GameSingleton::Get().GetPlayerType());
		if (CheckForDraw())
		{
			GameSingleton::Get().GetLevelController().GoToNextLevel();
			GameSingleton::Get().SetGameResult(EGameResult::DRAW);
			break;
		}
		if (CheckForWinCross())
		{
			GameSingleton::Get().GetLevelController().GoToNextLevel();
			GameSingleton::Get().SetGameResult(EGameResult::WIN);
			break;
		}
		if (CheckForWinZero())
		{
			GameSingleton::Get().GetLevelController().GoToNextLevel();
			GameSingleton::Get().SetGameResult(EGameResult::LOSE);
			break;
		}

		GetBestMove()->SetToken(GameSingleton::Get().GetAIPlayerType());
		if (CheckForWinZero())
		{
			GameSingleton::Get().GetLevelController().GoToNextLevel();
			GameSingleton::Get().SetGameResult(EGameResult::LOSE);
			break;
		}
		if (CheckForWinCross())
		{
			GameSingleton::Get().GetLevelController().GoToNextLevel();
			GameSingleton::Get().SetGameResult(EGameResult::WIN);
			break;
		}
		if (CheckForDraw())
		{
			GameSingleton::Get().GetLevelController().GoToNextLevel();
			GameSingleton::Get().SetGameResult(EGameResult::DRAW);
			break;
		}
		break;
	}
	default: break;
	}

	SelectCell(m_XCursor, m_YCursor);
}

void Field::FillCell(ETokenType InTokenType)
{
	_STL_VERIFY(m_SelectedCell, "[Field]: SelectedCell is nullptr");
	m_SelectedCell->SetToken(InTokenType);
}

void Field::SelectCell(int32_t InX, int32_t InY)
{
	if (m_SelectedCell == nullptr)
	{
		m_SelectedCell = GetCell(0, 0);
	}

	_STL_VERIFY(m_SelectedCell, "[Field]: SelectedCell is nullptr");
	m_SelectedCell->SetSelected(false);

	m_SelectedCell = GetCell(InX, InY);
	_STL_VERIFY(m_SelectedCell, "[Field]: SelectedCell is nullptr");
	m_SelectedCell->SetSelected(true);
}

bool Field::IsSelectionEmpty()
{
	_STL_VERIFY(m_SelectedCell, "[Field]: SelectedCell is nullptr");
	return m_SelectedCell->IsEmpty();
}

void Field::SelectStartCell()
{
	SelectCell(0, 0);
}

bool Field::CheckForWinCross()
{
	// Check columns
	bool IsDiagonal = true;
	for (int32_t x = 0; x < m_DimentionAmount; ++x)
	{
		bool IsColumnWinner = true;
		for (int32_t y = 0; y < m_DimentionAmount; ++y)
		{
			if (!GetCell(x, y)->IsCross() || GetCell(x, y)->IsEmpty())
			{
				if (x == y)
				{
					IsDiagonal = false;
				}
				IsColumnWinner = false;
			}
		}
		if (IsColumnWinner)
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
		// column?
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

// TODO: Add validity checks
int32_t Field::Minimax(Field* InCopyField, int32_t InDepth, bool IsMaximazing, int32_t InEmptyCellCount)
{
	if (m_DimentionAmount > 5 && InEmptyCellCount > m_DimentionAmount * 2)
	{
		return rand() % 5;
	}

	if (InDepth > 2)
	{
		return 0;
	}
	if (InCopyField->CheckForWinZero())
	{
		return GameSingleton::Get().GetAIPlayerType() == ETokenType::CROSS ? -1 : 1;
	}
	if (InCopyField->CheckForWinCross())
	{
		return GameSingleton::Get().GetAIPlayerType() == ETokenType::CROSS ? 1 : -1;
	}
	if (InCopyField->CheckForDraw())
	{
		return 0;
	}

	if (IsMaximazing)
	{
		int32_t BestScore = -10000000;
		for (int32_t x = 0; x < m_DimentionAmount; ++x)
		{
			for (int32_t y = 0; y < m_DimentionAmount; ++y)
			{
				if (InCopyField->GetCell(x, y)->IsEmpty())
				{
					InCopyField->GetCell(x, y)->SetToken(GameSingleton::Get().GetAIPlayerType());
					BestScore = std::max(BestScore, Minimax(InCopyField, InDepth + 1, false, InEmptyCellCount));
					InCopyField->GetCell(x, y)->SetEmpty();
				}
			}
		}
		return BestScore;
	}
	else
	{
		int32_t BestScore = 10000000;
		for (int32_t x = 0; x < m_DimentionAmount; ++x)
		{
			for (int32_t y = 0; y < m_DimentionAmount; ++y)
			{
				if (InCopyField->GetCell(x, y)->IsEmpty())
				{
					InCopyField->GetCell(x, y)->SetToken(GameSingleton::Get().GetPlayerType());
					BestScore = std::min(BestScore, Minimax(InCopyField, InDepth + 1, true, InEmptyCellCount));
					InCopyField->GetCell(x, y)->SetEmpty();
				}
			}
		}
		return BestScore;
	}
}

int32_t Field::CountEmptyCells() 
{
	int32_t Counter = 0;
	for (int32_t x = 0; x < m_DimentionAmount; ++x)
	{
		for (int32_t y = 0; y < m_DimentionAmount; ++y)
		{
			if (GetCell(x, y)->IsEmpty())
			{
				Counter++;
			}
		}
	}
	return Counter;
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
				Copy.GetCell(x, y)->SetToken(GameSingleton::Get().GetAIPlayerType());
				const int32_t Score = Minimax(&Copy, 0, false, CountEmptyCells());

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

EGameResult Field::CheckForGameResult()
{
	const ETokenType PlayerType = GameSingleton::Get().GetPlayerType();
	if (CheckForWinZero())
	{
		return PlayerType == ETokenType::ZERO ? EGameResult::WIN : EGameResult::LOSE;
	}
	if (CheckForWinCross())
	{
		return PlayerType == ETokenType::CROSS ? EGameResult::WIN : EGameResult::LOSE;
	}
	if (CheckForDraw())
	{
		return EGameResult::DRAW;
	}
	return EGameResult::None;
}

FieldCell* Field::GetCell(int32_t InX, int32_t InY)
{
	const int32_t CellIndex = (InX + 1) + m_DimentionAmount * InY;
	return &m_Cells.at(CellIndex);
}
