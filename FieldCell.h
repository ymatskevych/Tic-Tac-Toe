#pragma once

#include <string>
#include "FieldData.h"

enum class ETokenType;

class FieldCell
{
public:

	void SetSelected(bool InSelect);
	void SetToken(ETokenType InTokenType);
	void SetEmpty();

	std::string GetSymbol();

	bool IsCross() const;
	bool IsZero() const;
	bool IsEmpty() const;
	
private:

	void Select();
	void UnSelect();

	EFieldCellStatus m_Status = EFieldCellStatus::EMPTY;
};
