#pragma once

#include <string_view>
#include <array>
#include <variant>

#include <Phonem.hpp>
#include <PhonemEquivalent.hpp>

namespace YololTranslator
{

struct PhonemUniqueTranslation
{
	Phonem phonem;
	std::array<PhonemEquivalent, 10> _equivalents; // TODO: shrink to fit later with generated constant
};

struct PhonemCompositionTranslation
{
	std::array<Phonem, 5> phonem; // TODO: shrink to fit later with generated constant
	std::size_t nb_phonem; // Better than use an array of optional I think
	std::array<PhonemEquivalent, 10> _equivalents; // TODO: shrink to fit later with generated constant
};

using PhonemTranslation = std::variant<PhonemUniqueTranslation, PhonemCompositionTranslation>;

} // namespace YololTranslator
