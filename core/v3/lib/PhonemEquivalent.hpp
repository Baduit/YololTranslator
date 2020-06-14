#pragma once

#include <string_view>

namespace YololTranslator
{

struct PhonemEquivalent
{
	std::string_view chars;
	std::size_t weight;

	// use a bitset if there is a need to reduce memory space
	bool can_begin;
	bool can_middle;
	bool can_end;
};

} // namespace YololTranslator