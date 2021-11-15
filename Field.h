#pragma once
#include <vector>

#include "FieldCell.h"
#include "GameSingleton.h"
#include "Datas/KeyboardData.h"

/*
 * LOGIC
 */
class Field
{
public:

	// int32_t InDimentionAmount
	void GenerateCells()
	{
		for (int32_t x = 0; x <= 6; ++x)
		{
			for (int32_t y = 0; y <= 6; ++y)
			{
				m_Cells.push_back(FieldCell(x, y));
			}
		}
	}

	void ProcessInput()
	{
		Key Input = GameSingleton::Get().GetInputController().GetLastInput();
		switch (Input)
		{
		case Key::UP:
			{
				m_YCursor = std::max(m_YCursor, m_YCursor - 1);
				break;
			}
		case Key::DOWN:
			{
				m_YCursor = std::min(m_YCursor, m_YCursor + 1);
				break;
			}
		case Key::LEFT:
			{
				m_XCursor = std::min(m_XCursor, m_XCursor - 1);
				break;
			}
		case Key::RIGHT:
			{
				m_XCursor = std::max(m_XCursor, m_XCursor + 1);
				break;
			}
		case Key::ENTER:
			{
				break;
			}
		default: break;
		}

		SelectCell();
	}

private:

	void SelectCell()
	{
		SelectedCell = GetCell(m_XCursor, m_YCursor);
		SelectedCell->SetSelected();
	}

	void UpdateWidget() {}

	void MoveSelection(int32_t InX, int32_t InY)
	{
		std::min(std::max(m_XCursor, m_XCursor + InX), m_XCursor + InX);
	}

	FieldCell* GetCell(int32_t InX, int32_t InY)
	{
		const int32_t CellIndex = (InX + 1) + 6 * InY;
		return &m_Cells.at(CellIndex);
	}

	std::vector<FieldCell> m_Cells;
	std::vector<FieldCell> m_FreeCells;

	FieldCell* SelectedCell = nullptr;

	int32_t m_XCursor = 0;
	int32_t m_YCursor = 0;

	// FieldWidget REF
};