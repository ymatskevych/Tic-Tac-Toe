#pragma once

#include <cstdint>
#include <string>
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

	void FillCell(bool IsZero)
	{
		if (IsZero)
		{
			if (m_Status == EFieldCellStatus::SELECTED)
			{
				// gamesingleton.getplayetype
				m_Status = EFieldCellStatus::ZERO_SELECTED;
			}
			else
			{
				m_Status = EFieldCellStatus::ZERO;
			}
		}
		if (m_Status == EFieldCellStatus::SELECTED)
		{
			// gamesingleton.getplayetype
			m_Status = EFieldCellStatus::CROSS_SELECTED;
		}
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
		else
		{
			m_Status = EFieldCellStatus::SELECTED;
		}
	}

	void UnSelect()
	{
		if (m_Status == EFieldCellStatus::CROSS_SELECTED)
		{
			m_Status = EFieldCellStatus::CROSS;
		}
		else if (m_Status == EFieldCellStatus::ZERO_SELECTED)
		{
			m_Status = EFieldCellStatus::ZERO;
		}
		else
		{
			m_Status = EFieldCellStatus::EMPTY;
		}
	}

	void SetZero()
	{
		if (m_Status == EFieldCellStatus::SELECTED)
		{
			m_Status = EFieldCellStatus::ZERO_SELECTED;
		}
		else
		{
			m_Status = EFieldCellStatus::ZERO;
		}
	}

	void SetCross()
	{
		if (m_Status == EFieldCellStatus::SELECTED)
		{
			m_Status = EFieldCellStatus::CROSS_SELECTED;
		}
		else
		{
			m_Status = EFieldCellStatus::CROSS;
		}
	}

	void SetEmpty()
	{
		if (m_Status == EFieldCellStatus::CROSS_SELECTED
			|| m_Status == EFieldCellStatus::ZERO_SELECTED)
		{
			m_Status = EFieldCellStatus::SELECTED;
		}
		else
		{
			m_Status = EFieldCellStatus::EMPTY;
		}
	}

	std::string GetSymbol()
	{
		if (m_Status == EFieldCellStatus::CROSS)
		{
			return "x";
		}
		if (m_Status == EFieldCellStatus::ZERO)
		{
			return "o";
		}
		if (m_Status == EFieldCellStatus::CROSS_SELECTED
			|| m_Status == EFieldCellStatus::ZERO_SELECTED)
		{
			return "!";
		}
		if(m_Status == EFieldCellStatus::SELECTED)
		{
			return "?";
		}
		return " ";
	}

	bool IsCross() const
	{
		return m_Status == EFieldCellStatus::CROSS || m_Status == EFieldCellStatus::CROSS_SELECTED;
	}

	bool IsZero() const
	{
		return m_Status == EFieldCellStatus::ZERO || m_Status == EFieldCellStatus::ZERO_SELECTED;
	}

	bool IsEmpty() const
	{
		return m_Status == EFieldCellStatus::EMPTY;
	}
	
private:

	EFieldCellStatus m_Status = EFieldCellStatus::EMPTY;

	FieldCellCoord m_Coord;
};