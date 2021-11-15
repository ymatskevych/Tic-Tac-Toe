#pragma once
#include <vector>

#include "FieldCell.h"
#include "Datas/GameData.h"
#include "Interfaces/ITickable.h"

/*
 * LOGIC
 */
class Field : public ITickable
{
public:

	void GenerateCells();

	void Tick(float InDeltaTime) override;
	void ProcessInput();
	std::string GetFieldAsString();

//private:

	void FillCell(bool IsZero);
	void SelectCell();

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