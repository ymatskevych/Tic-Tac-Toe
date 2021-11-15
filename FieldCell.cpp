#include "FieldCell.h"

#include "GameSingleton.h"

void FieldCell::FillCell(EPlayerType InPlayerType)
{
	if (InPlayerType == EPlayerType::ZERO)
	{
		m_Status = m_Status == EFieldCellStatus::SELECTED ? EFieldCellStatus::ZERO_SELECTED : EFieldCellStatus::ZERO;
	}
	else if (InPlayerType == EPlayerType::CROSS)
	{
		m_Status = m_Status == EFieldCellStatus::SELECTED ? EFieldCellStatus::CROSS_SELECTED : EFieldCellStatus::CROSS;
	}
}

void FieldCell::Select()
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

void FieldCell::UnSelect()
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

void FieldCell::SetToken(EPlayerType InPlayerType)
{
	if (InPlayerType == EPlayerType::CROSS)
	{
		m_Status = m_Status == EFieldCellStatus::SELECTED ? EFieldCellStatus::CROSS_SELECTED : EFieldCellStatus::CROSS;
	}
	else if (InPlayerType == EPlayerType::ZERO)
	{
		m_Status = m_Status == EFieldCellStatus::SELECTED ? EFieldCellStatus::ZERO_SELECTED : EFieldCellStatus::ZERO;
	}
}

void FieldCell::SetEmpty()
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

std::string FieldCell::GetSymbol()
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
	if (m_Status == EFieldCellStatus::SELECTED)
	{
		return "?";
	}
	return " ";
}

bool FieldCell::IsCross() const
{
	return m_Status == EFieldCellStatus::CROSS || m_Status == EFieldCellStatus::CROSS_SELECTED;
}

bool FieldCell::IsZero() const
{
	return m_Status == EFieldCellStatus::ZERO || m_Status == EFieldCellStatus::ZERO_SELECTED;
}

bool FieldCell::IsEmpty() const
{
	return m_Status == EFieldCellStatus::EMPTY;
}
