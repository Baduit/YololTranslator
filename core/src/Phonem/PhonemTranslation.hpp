#pragma once

#include <string_view>
#include <vector>
#include <variant>
#include <type_traits>

#include <Phonem/Phonem.hpp>
#include <Phonem/PhonemEquivalent.hpp>

struct PhonemUniqueTranslation
{
	Phonem phonem;
	std::vector<PhonemEquivalent> _equivalents;
};

struct PhonemCompositionTranslation
{
	const auto& get_phonems() const { return phonem; }

	std::vector<Phonem> phonem;
	std::vector<PhonemEquivalent> _equivalents;
};

struct PhonemTranslation
{
	PhonemTranslation(PhonemUniqueTranslation t):
		translation(t) 
	{}

	PhonemTranslation(PhonemCompositionTranslation t):
		translation(t) 
	{}

	bool is_unique() const
	{
		return std::holds_alternative<PhonemUniqueTranslation>(translation);
	}

	Phonem get_first_phonem() const
	{
		return std::visit(
			[](const auto& t)
			{
				using T = std::decay_t<decltype(t)>;
				if constexpr (std::is_same_v<T, PhonemUniqueTranslation>)
					return t.phonem;
				else if constexpr (std::is_same_v<T, PhonemCompositionTranslation>)
					return t.phonem.front();
        	}, translation);
	}

	const auto& get_equivalents() const
	{
		return std::visit(
			[](const auto& t) -> const std::vector<PhonemEquivalent>&
			{
				return t._equivalents;
        	}, translation);
	}

	std::size_t get_equivalents_size() const
	{
		return std::visit(
			[](const auto& t)
			{
				return t._equivalents.size();
        	}, translation);
	}

	std::size_t get_nb_phonems() const
	{
		return std::visit(
			[](const auto& t)
			{
				using T = std::decay_t<decltype(t)>;
				if constexpr (std::is_same_v<T, PhonemUniqueTranslation>)
					return static_cast<std::size_t>(1);
				else if constexpr (std::is_same_v<T, PhonemCompositionTranslation>)
					return t.phonem.size();
        	}, translation);
	}

	template <typename It>
	bool match_phonems(It begin, It end) const
	{
		return std::visit(
			[&](const auto& t)
			{
				using T = std::decay_t<decltype(t)>;
				if constexpr (std::is_same_v<T, PhonemUniqueTranslation>)
				{
					return *begin == t.phonem;
				}
				else if constexpr (std::is_same_v<T, PhonemCompositionTranslation>)
				{
					if (static_cast<decltype(end- begin)>(get_nb_phonems()) > (end - begin))
						return false;
					
					for (std::size_t i = 0; i < get_nb_phonems(); ++i)
					{
						if (*(begin + static_cast<int>(i)) != t.get_phonems()[i])
							return false;
					}
					return true;
				}
        	}, translation);
	}

	std::variant<PhonemUniqueTranslation, PhonemCompositionTranslation> translation;
};
