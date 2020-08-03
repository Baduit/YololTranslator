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

	bool operator==(const PhonemEquivalent&) const = default;
	auto operator<=>(const PhonemEquivalent&) const = default;
};
