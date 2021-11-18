#pragma once

#include <string>
#include <vector>

#include "FieldCell.h"
#include "Datas/GameData.h"
#include "Interfaces/ITickable.h"

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

	void Initialize();

	// ITickable interface
	void Tick(float InDeltaTime) override;
	void ProcessInput();

	void SetDimentionAmount(int32_t InDimentionAmount) { m_DimentionAmount = InDimentionAmount; }
	int32_t GetDimentionAmount() const { return m_DimentionAmount; }

	std::string GetFieldAsString();

	EGameResult CheckForGameResult();

private:

	void GenerateCells();
	void FillCell(ETokenType InTokenType);
	void SelectCell(int32_t InX, int32_t InY);
	bool IsSelectionEmpty();

	void SelectStartCell();

	// TODO: it can be refactored, but not today
	bool CheckForWinCross();
	bool CheckForWinZero();
	bool CheckForDraw();

	int32_t Minimax(Field* CopyField, bool IsMaximazing);

	FieldCell* GetBestMove();

	FieldCell* GetCell(int32_t InX, int32_t InY);

	std::vector<FieldCell> m_Cells;

	FieldCell* m_SelectedCell = nullptr;

	int32_t m_XCursor = 0;
	int32_t m_YCursor = 0;

	int32_t m_DimentionAmount = DEFAULT_DIMENTION;
};