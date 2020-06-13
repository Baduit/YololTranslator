#pragma once

#include <string_view>
#include <array>
#include <variant>

#include <Phonem.hpp>
#include <PhonemEquivalent.hpp>

namespace YololTranslator
{

constexpr std::size_t MAX_NB_PHONEM_EQUIVALENT = 10; // TODO: shrink to fit later with generated constant
constexpr std::size_t MAX_NB_PHONEM_IN_COMPOSITION = 5; // TODO: shrink to fit later with generated constant

struct PhonemUniqueTranslation
{
	Phonem phonem;
	
	std::size_t nb_equivalents;
	std::array<PhonemEquivalent, MAX_NB_PHONEM_EQUIVALENT> _equivalents;
};

struct PhonemCompositionTranslation
{
	std::size_t nb_phonem;
	std::array<Phonem, MAX_NB_PHONEM_IN_COMPOSITION> phonem;

	std::size_t nb_equivalents;
	std::array<PhonemEquivalent, MAX_NB_PHONEM_EQUIVALENT> _equivalents;
};

// Due to a bug in std::variant I can't use a std::variant in constexpr expression (according to the standard I should normally be able to do it)
//using PhonemTranslation = std::variant<PhonemUniqueTranslation, PhonemCompositionTranslation>;
struct PhonemTranslation
{
	constexpr PhonemTranslation(PhonemUniqueTranslation t):
		type(Type::UNIQUE), translation(t) 
	{}

	constexpr PhonemTranslation(PhonemCompositionTranslation t):
		type(Type::COMPOSITION), translation(t) 
	{}

	constexpr const auto& get_equivalents() const
	{
		return (type == Type::UNIQUE) ? translation.unique._equivalents : translation.composition._equivalents;
	}

	constexpr std::size_t get_equivalents_size() const
	{
		return (type == Type::UNIQUE) ? translation.unique.nb_equivalents : translation.composition.nb_equivalents;
	}

	constexpr std::size_t get_nb_phonems() const
	{
		return (type == Type::UNIQUE) ? 1 : translation.composition.nb_phonem;
	}

	enum class Type
	{
		UNIQUE,
		COMPOSITION
	};

	Type type;

	union TUnion
	{
		constexpr TUnion(PhonemUniqueTranslation t):
			unique(t)
		{}

		constexpr TUnion(PhonemCompositionTranslation t):
			composition(t)
		{}

		PhonemUniqueTranslation unique;
		PhonemCompositionTranslation composition;
	} translation;
};

} // namespace YololTranslator
