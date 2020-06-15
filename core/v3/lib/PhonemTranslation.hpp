#pragma once

#include <string_view>
#include <array>
#include <variant>

#include <Phonem.hpp>
#include <PhonemEquivalent.hpp>
#include <PhonemList.hpp>

namespace YololTranslator
{

constexpr std::size_t MAX_NB_PHONEM_EQUIVALENT = 10; // TODO: shrink to fit later with generated constant
constexpr std::size_t MAX_NB_PHONEM_IN_COMPOSITION = 5; // TODO: shrink to fit later with generated constant

struct PhonemUniqueTranslation
{
	template <typename ...Args>
	constexpr PhonemUniqueTranslation(Phonem p, Args&&... args):
		phonem(p),
		nb_equivalents(sizeof...(args)),
		_equivalents({ args... })
	{}
	Phonem phonem;
	
	std::size_t nb_equivalents;
	std::array<PhonemEquivalent, MAX_NB_PHONEM_EQUIVALENT> _equivalents;
};

struct PhonemCompositionTranslation
{
	PhonemCompositionTranslation(const PhonemCompositionTranslation&) = default;
	PhonemCompositionTranslation& operator=(const PhonemCompositionTranslation&) = default;
	
	PhonemCompositionTranslation(PhonemCompositionTranslation&&) = default;
	PhonemCompositionTranslation& operator=(PhonemCompositionTranslation&&) = default;

	template <typename ...Args>
	constexpr PhonemCompositionTranslation(const PhonemList& p, Args&&... args):
		phonem(p),
		nb_equivalents(sizeof...(args)),
		_equivalents({ args... })
	{}

	const auto& get_phonems() const { return phonem.phonems; }

	PhonemList phonem;

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
		return (type == Type::UNIQUE) ? 1 : translation.composition.phonem.size;
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
				if (*(begin + i) != translation.composition.get_phonems()[i])
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
