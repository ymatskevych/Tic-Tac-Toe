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
		FieldCell* Cell = GetBestMove();
		_STL_VERIFY(Cell, "[Field]: Cell in nullptr");

		Cell->SetToken(GameSingleton::Get().GetAIPlayerType());
	}

	SelectStartCell();

	m_Initialized = true;
}

void Field::Tick(float InDeltaTime)
{
	if (_kbhit() && m_Initialized)
	{
		ProcessInput();
	}
}

// TODO: move to input controller 
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
		PlaceToken();
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

bool Field::IsSelectionEmpty() const
{
	_STL_VERIFY(m_SelectedCell, "[Field]: SelectedCell is nullptr");
	return m_SelectedCell->IsEmpty();
}

void Field::SelectStartCell()
{
	SelectCell(0, 0);
}

bool Field::CheckForWin(ETokenType InTokenType) const
{
	// Check columns
	bool IsDiagonal = true;
	for (int32_t x = 0; x < m_DimentionAmount; ++x)
	{
		bool IsColumnWinner = true;
		for (int32_t y = 0; y < m_DimentionAmount; ++y)
		{
			const FieldCell* Cell = GetCell(x, y);
			_STL_VERIFY(Cell, "[Field]: Cell is nullptr");

			if (!Cell->IsTokenType(InTokenType) || Cell->IsEmpty())
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
			const FieldCell* Cell = GetCell(x, y);
			_STL_VERIFY(Cell, "[Field]: Cell is nullptr");

			if (!Cell->IsTokenType(InTokenType) || Cell->IsEmpty())
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

bool Field::CheckForDraw() const
{
	for (int32_t x = 0; x < m_DimentionAmount; ++x)
	{
		for (int32_t y = 0; y < m_DimentionAmount; ++y)
		{
			const FieldCell* Cell = GetCell(x, y);
			_STL_VERIFY(Cell, "[Field]: Cell is nullptr");

			if (Cell->IsEmpty())
			{
				return false;
			}
		}
	}
	return true;
}

void Field::PlaceToken()
{
	if (!IsSelectionEmpty())
	{
		return;
	}

	GameSingleton& _GameSingleton = GameSingleton::Get();
	LevelController& _LevelController = _GameSingleton.GetLevelController();
	FillCell(_GameSingleton.GetPlayerType());
	if (CheckForDraw())
	{
		_LevelController.GoToNextLevel();
		_GameSingleton.SetGameResult(EGameResult::DRAW);
		return;
	}
	if (CheckForWin(ETokenType::CROSS))
	{
		_LevelController.GoToNextLevel();
		_GameSingleton.SetGameResult(EGameResult::WIN);
		return;
	}
	if (CheckForWin(ETokenType::ZERO))
	{
		_LevelController.GoToNextLevel();
		_GameSingleton.SetGameResult(EGameResult::LOSE);
		return;
	}

	FieldCell* AIMoveCell = GetBestMove();
	_STL_VERIFY(AIMoveCell, "[Field]: AIMoveCell is nullptr");

	AIMoveCell->SetToken(GameSingleton::Get().GetAIPlayerType());
	if (CheckForWin(ETokenType::CROSS))
	{
		_LevelController.GoToNextLevel();
		_GameSingleton.SetGameResult(EGameResult::WIN);
		return;
	}
	if (CheckForWin(ETokenType::ZERO))
	{
		_LevelController.GoToNextLevel();
		_GameSingleton.SetGameResult(EGameResult::LOSE);
		return;
	}
	if (CheckForDraw())
	{
		_LevelController.GoToNextLevel();
		_GameSingleton.SetGameResult(EGameResult::DRAW);
		return;
	}
}

// TODO: Add validity checks
int32_t Field::Minimax(Field* InCopyField, int32_t InDepth, bool IsMaximazing, int32_t InEmptyCellCount)
{
	/*
	 * This cool hack was added here because minimax algorithm complexity is too hight
	 * for hight dimensional tic tac toe :( 
	 */
	if (m_DimentionAmount > 5 && InEmptyCellCount > m_DimentionAmount * 2)
	{
		return rand() % 5;
	}
	if (InDepth > 2)
	{
		return 0;
	}


	_STL_VERIFY(InCopyField, "[Field]: AIMoveCell is nullptr");
	if (InCopyField->CheckForWin(ETokenType::ZERO))
	{
		return GameSingleton::Get().GetAIPlayerType() == ETokenType::CROSS ? -1 : 1;
	}
	if (InCopyField->CheckForWin(ETokenType::CROSS))
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
				FieldCell* Cell = InCopyField->GetCell(x, y);
				_STL_VERIFY(Cell, "[Field]: Cell is nullptr");
				if (Cell->IsEmpty())
				{
					Cell->SetToken(GameSingleton::Get().GetAIPlayerType());
					BestScore = std::max(BestScore, Minimax(InCopyField, InDepth + 1, false, InEmptyCellCount));
					Cell->SetEmpty();
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
				FieldCell* Cell = InCopyField->GetCell(x, y);
				_STL_VERIFY(Cell, "[Field]: Cell is nullptr");
				if (Cell->IsEmpty())
				{
					Cell->SetToken(GameSingleton::Get().GetPlayerType());
					BestScore = std::min(BestScore, Minimax(InCopyField, InDepth + 1, true, InEmptyCellCount));
					Cell->SetEmpty();
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
			const FieldCell* Cell = GetCell(x, y);
			_STL_VERIFY(Cell, "[Field]: Cell is nullptr");
			if (Cell->IsEmpty())
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
			FieldCell* Cell = GetCell(x, y);
			_STL_VERIFY(Cell, "[Field]: Cell is nullptr");
			if (Cell->IsEmpty())
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
				FieldCell* Cell = GetCell((i - 1) / 2, j / 2);
				_STL_VERIFY(Cell, "[Field]: Cell is nullptr");

				// x = (i - 1) / 2; y = j / 2
				FieldDraw += j % 2 == 0 ? "|" : Cell->GetSymbol();
			}
		}
		FieldDraw += "\n";
	}
	return FieldDraw;
}

EGameResult Field::CheckForGameResult() const
{
	const ETokenType PlayerType = GameSingleton::Get().GetPlayerType();
	if (CheckForWin(ETokenType::ZERO))
	{
		return PlayerType == ETokenType::ZERO ? EGameResult::WIN : EGameResult::LOSE;
	}
	if (CheckForWin(ETokenType::CROSS))
	{
		return PlayerType == ETokenType::CROSS ? EGameResult::WIN : EGameResult::LOSE;
	}
	if (CheckForDraw())
	{
		return EGameResult::DRAW;
	}
	return EGameResult::None;
}

const FieldCell* Field::GetCell(int32_t InX, int32_t InY) const
{
	const int32_t CellIndex = (InX + 1) + m_DimentionAmount * InY;
	return &m_Cells.at(CellIndex);
}

FieldCell* Field::GetCell(int32_t InX, int32_t InY)
{
	const int32_t CellIndex = (InX + 1) + m_DimentionAmount * InY;
	return &m_Cells.at(CellIndex);
}
