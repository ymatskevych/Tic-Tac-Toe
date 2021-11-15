#pragma once

#include <cstdint>

#include "FieldData.h"

struct FieldCellCoord
{
	int32_t X;
	int32_t Y;
};

class FieldCell
{
public:

	FieldCell() = delete;

	FieldCell(int32_t InX, int32_t InY)
	{
		FieldCellCoord Coord;
		Coord.X = InX;
		Coord.Y = InY;
		m_Coord = Coord;
	}

	void SetSelected()
	{
		if (m_Status == EFieldCellStatus::ZERO)
		{
			m_Status = EFieldCellStatus::ZERO_SELECTED;
		}
		else if (m_Status == EFieldCellStatus::CROSS)
		{
			m_Status = EFieldCellStatus::CROSS_SELECTED;
		}
	}

	//void SetStatus(EFieldCellStatus InStatus) { m_Status = InStatus; }
	
private:

	EFieldCellStatus m_Status = EFieldCellStatus::None;

	FieldCellCoord m_Coord;
};