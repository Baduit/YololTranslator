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
	//Phonem phonem;
	//std::array<PhonemEquivalent, 10> _equivalents; // TODO: shrink to fit later with generated constant
};

struct PhonemCompositionTranslation
{
	//std::array<Phonem, 5> phonem; // TODO: shrink to fit later with generated constant
	//std::size_t nb_phonem; // Better than use an array of optional I think
	//std::array<PhonemEquivalent, 10> _equivalents; // TODO: shrink to fit later with generated constant
};

// Due to a bug in std::variant I can't use a std::variant in constexpr expression (according to the standard I should normally be able to do it)
//using PhonemTranslation = std::variant<PhonemUniqueTranslation, PhonemCompositionTranslation>;
struct PhonemTranslation
{
	constexpr PhonemTranslation(PhonemUniqueTranslation t):
		type(Type::UNIQUE)
	{
		translation.unique = t;
	}

	constexpr PhonemTranslation(PhonemCompositionTranslation t):
		type(Type::COMPOSITION)
	{
		translation.composition = t;
	}

	enum class Type
	{
		UNIQUE,
		COMPOSITION
	};

	Type type;

	union
	{
		PhonemUniqueTranslation unique;
		PhonemCompositionTranslation composition;
	} translation;
};

} // namespace YololTranslator
