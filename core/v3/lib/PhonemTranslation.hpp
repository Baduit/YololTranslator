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

	template <typename It>
	constexpr bool match_phonems(It begin, It end)
	{
		if (type == Type::UNIQUE)
		{
			return *begin == translation.unique.phonem;
		}
		else // Type::COMPOSITION
		{
			if (static_cast<decltype(end- begin)>(get_nb_phonems()) > (end - begin))
				return false;
			
			for (std::size_t i = 0; i < get_nb_phonems(); ++i)
			{
				if (*(begin + i) != translation.composition.phonem[i])
					return false;
			}
			return true;
		}
	}

	enum class Type
	{
		UNIQUE,
		COMPOSITION
	};

	Type type;

	// Due to a bug in std::variant I can't use a std::variant in constexpr expression (according to the standard I should normally be able to do it)
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
