#pragma once

#include <vector>

#include <utilities/Random.hpp>


struct WordTranslation final
{
	std::size_t weight;
	std::string chars;
};


class WordTranslationContainer
{
	public:
		WordTranslationContainer() = default;

		WordTranslationContainer(const WordTranslationContainer&) = default;
		WordTranslationContainer& operator=(const WordTranslationContainer&) = default;

		WordTranslationContainer(WordTranslationContainer&&) = default;
		WordTranslationContainer& operator=(WordTranslationContainer&&) = default;

		void load(std::vector<WordTranslation> new_translations)
		{
			if (_translation.empty())
				_translation = std::move(new_translations);
			else
				_translation.insert(std::end(_translation),
							std::make_move_iterator(std::begin(new_translations)),
							std::make_move_iterator(std::end(new_translations)));	
		}

		void clear()
		{
			_translation.clear();
		}

		std::string_view operator()() const
		{
			return get_random_translation();
		}

		std::string_view get_random_translation() const
		{
			return get_translation(Random::rand(get_max_random_range()));
		}

		auto operator<=>(const WordTranslationContainer&) const = default;

	private:
		std::size_t get_max_random_range() const noexcept
		{
			std::size_t result = 0;
			for (const auto& t: _translation)
			{
				result += t.weight;
			}
			return result;
		}

		std::string_view get_translation(std::size_t weighted_index) const
		{
			std::size_t i = 0;
			for (const auto& t: _translation)
			{
				i += t.weight;
				if (i >= weighted_index)
					return t.chars;
			}
			throw std::runtime_error("WordTranslationContainer failed while choosing a translation.");
		}

	private:
		std::vector<WordTranslation> _translation;
};
