#pragma once


namespace VectorTools
{
	template<typename T>
	bool Contains(std::vector<T> InVector, int32_t InIndex)
	{
		return !(InIndex < 0 || InIndex > InVector.size());
	}
}