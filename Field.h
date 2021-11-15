#pragma once

#include <string>
#include <vector>

#include "FieldCell.h"
#include "Datas/GameData.h"
#include "Interfaces/ITickable.h"

enum class EPlayerType;

enum class EGameResult
{
	None = -2,

	LOSE = -1,
	DRAW = 0,
	WIN = 1
};

class Field : public ITickable
{
public:

	void GenerateCells();

	void Tick(float InDeltaTime) override;
	void ProcessInput();
	std::string GetFieldAsString();

	EGameResult CheckForGameResult();

private:

	void FillCell(EPlayerType InPlayerType);
	void SelectCell();

	// TODO: it can be refactored, but not today
	bool CheckForWinCross();
	bool CheckForWinZero();
	bool CheckForDraw();

	int32_t Minimax(Field* CopyField, int32_t depth, bool IsMaximazing);

	FieldCell* GetBestMove();

	FieldCell* GetCell(int32_t InX, int32_t InY);

	std::vector<FieldCell> m_Cells;
	std::vector<FieldCell> m_FreeCells;

	FieldCell* SelectedCell = nullptr;

	int32_t m_XCursor = 0;
	int32_t m_YCursor = 0;

	int32_t m_DimentionAmount = DEFAULT_DIMENTION;
};