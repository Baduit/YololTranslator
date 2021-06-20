#pragma once

#include <string>
#include <compare>

struct PhonemEquivalent
{
	std::string chars;
	std::size_t weight = 0;

	bool can_begin = true;
	bool can_middle = true;
	bool can_end = true;

	bool operator==(const PhonemEquivalent& other) const
	{
		return
			chars == other.chars &&
			weight == other.weight &&
			can_begin == other.can_begin &&
			can_middle == other.can_middle &&
			can_end == other.can_end;
	}

	bool operator<(const PhonemEquivalent& other) const
	{
		if (chars != other.chars)
			return chars < other.chars;
		
		if (weight != other.weight)
			return weight < other.weight;
		
		if (can_begin != other.can_begin)
			return can_begin < other.can_begin;
		
		if (can_middle != other.can_middle)
			return can_middle < other.can_middle;
		
		return can_end < other.can_end;
	}
};
