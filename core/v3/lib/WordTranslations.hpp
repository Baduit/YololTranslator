#pragma once

#include <array>
#include <iostream>

#include <Random.hpp>
#include <TranslatorCallable.hpp>

namespace YololTranslator
{

struct WordTranslation final
{
	std::size_t weight;
	std::string_view chars;
};


template <std::size_t Size>
class WordTranslationContainer
{
	public:
		std::string_view operator()() const
		{
			return get_random_translation();
		}

		std::string_view get_random_translation() const
		{
			return get_translation(Random::rand(get_max_random_range()));
		}

	private:
		constexpr std::size_t get_max_random_range() const noexcept
		{
			std::size_t result = 0;
			for (const auto& t: _translation)
			{
				result += t.weight;
			}
			return result;
		}

		constexpr std::string_view get_translation(std::size_t weighted_index) const noexcept
		{
			std::size_t i = 0;
			for (const auto& t: _translation)
			{
				i += t.weight;
				if (i >= weighted_index)
					return t.chars;
			}
			return ""; // Should never happen
		}

	public: // Public for ugly massive aggregate initialisation
		std::array<WordTranslation, Size> _translation;
};

template <typename ...Args>
constexpr auto createWordTranslationContainer(Args&&... args)
{
	return WordTranslationContainer<sizeof...(args)>{args...};
}

} // namespace YololTranslator
