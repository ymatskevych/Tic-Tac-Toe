#pragma once

#include <string>
#include "FieldData.h"

enum class EPlayerType;

class FieldCell
{
public:

	void FillCell(EPlayerType InPlayerType);

	void Select();
	void UnSelect();

	void SetToken(EPlayerType InPlayerType);

	void SetEmpty();

	std::string GetSymbol();

	bool IsCross() const;
	bool IsZero() const;
	bool IsEmpty() const;
	
private:

	EFieldCellStatus m_Status = EFieldCellStatus::EMPTY;
};
