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

	// ITickable interface
	void Tick(float InDeltaTime) override;
	void ProcessInput();

	void Initialize();

	void SetDimentionAmount(int32_t InDimentionAmount) { m_DimentionAmount = InDimentionAmount; }
	int32_t GetDimentionAmount() const { return m_DimentionAmount; }

	std::string GetFieldAsString();

	EGameResult CheckForGameResult() const;

private:

	void GenerateCells();
	void FillCell(ETokenType InTokenType);
	void SelectCell(int32_t InX, int32_t InY);
	void SelectStartCell();

	bool IsSelectionEmpty() const;

	bool CheckForWin(ETokenType InTokenType) const;
	bool CheckForDraw() const;

	void PlaceToken();

	int32_t Minimax(Field* InCopyField, int32_t InDepth, bool IsMaximazing, int32_t EmptyCellCount);
	FieldCell* GetBestMove();

	int32_t CountEmptyCells();

	const FieldCell* GetCell(int32_t InX, int32_t InY) const;
	FieldCell* GetCell(int32_t InX, int32_t InY);

	std::vector<FieldCell> m_Cells;
	FieldCell* m_SelectedCell = nullptr;

	int32_t m_XCursor = 0;
	int32_t m_YCursor = 0;

	int32_t m_DimentionAmount = DEFAULT_DIMENTION;

	bool m_Initialized = false;
};