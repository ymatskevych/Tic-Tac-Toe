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

	bool IsTokenType(ETokenType InTokenType) const;
	bool IsEmpty() const;
	
private:

	void Select();
	void UnSelect();

	bool IsCross() const;
	bool IsZero() const;

	EFieldCellStatus m_Status = EFieldCellStatus::EMPTY;
};
