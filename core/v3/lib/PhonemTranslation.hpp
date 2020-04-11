#pragma once

#include <string_view>
#include <array>

#include <Phonem.hpp>
#include <PhonemEquivalent.hpp>

namespace YololTranslator
{

struct PhonemTranslation
{
	Phonem phonem;
	std::array<PhonemEquivalent, 10> _equivalents; // TODO: shrink to fit later with generated constant
};


} // namespace YololTranslator
