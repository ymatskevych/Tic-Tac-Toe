#include "FieldCell.h"

#include "GameSingleton.h"

//void FieldCell::FillCell(ETokenType InTokenType)
//{
//	if (InTokenType == ETokenType::ZERO)
//	{
//		m_Status = m_Status == EFieldCellStatus::SELECTED ? EFieldCellStatus::ZERO_SELECTED : EFieldCellStatus::ZERO;
//	}
//	else if (InTokenType == ETokenType::CROSS)
//	{
//		m_Status = m_Status == EFieldCellStatus::SELECTED ? EFieldCellStatus::CROSS_SELECTED : EFieldCellStatus::CROSS;
//	}
//}

void FieldCell::SetToken(ETokenType InTokenType)
{
	if (InTokenType == ETokenType::CROSS)
	{
		m_Status = m_Status == EFieldCellStatus::SELECTED ? EFieldCellStatus::CROSS_SELECTED : EFieldCellStatus::CROSS;
	}
	else if (InTokenType == ETokenType::ZERO)
	{
		m_Status = m_Status == EFieldCellStatus::SELECTED ? EFieldCellStatus::ZERO_SELECTED : EFieldCellStatus::ZERO;
	}
}

void FieldCell::SetSelected(bool InSelect)
{
	InSelect ? Select() : UnSelect();
}

void FieldCell::Select()
{
	switch (m_Status)
	{
	case EFieldCellStatus::ZERO:
		{
			m_Status = EFieldCellStatus::ZERO_SELECTED;
			break;
		}
	case EFieldCellStatus::CROSS:
		{
			m_Status = EFieldCellStatus::CROSS_SELECTED;
			break;
		}
	default:
		{
			m_Status = EFieldCellStatus::SELECTED;
		}
	}
}

void FieldCell::UnSelect()
{
	switch (m_Status)
	{
	case EFieldCellStatus::ZERO_SELECTED:
		{
			m_Status = EFieldCellStatus::ZERO;
			break;
		}
	case EFieldCellStatus::CROSS_SELECTED:
		{
			m_Status = EFieldCellStatus::CROSS;
			break;
		}
	default:
		{
			m_Status = EFieldCellStatus::EMPTY;
		}
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
	return m_Status == EFieldCellStatus::EMPTY || m_Status == EFieldCellStatus::SELECTED;
}
