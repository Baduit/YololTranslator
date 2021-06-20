#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <compare>

struct WordTranslation final
{
	bool operator==(const WordTranslation& other) const
	{
		return
			weight == other.weight &&
			chars == other.chars;
	}

	bool operator!=(const WordTranslation& other) const { return !(*this == other); }

	bool operator<(const WordTranslation& other) const
	{
		if (chars != other.chars)
			return chars < other.chars;
		return weight < other.weight;
	}

	std::string chars;
	std::size_t weight;
};


class WordTranslationContainer
{
	public:
		WordTranslationContainer() = default;

		WordTranslationContainer(const WordTranslationContainer&) = default;
		WordTranslationContainer& operator=(const WordTranslationContainer&) = default;

		WordTranslationContainer(WordTranslationContainer&&) = default;
		WordTranslationContainer& operator=(WordTranslationContainer&&) = default;

		bool operator==(const WordTranslationContainer& other) const { return _translation == other._translation; }
		bool operator!=(const WordTranslationContainer& other) const { return !(*this == other); }
		bool operator<(const WordTranslationContainer& other) const { return _translation < other._translation; }

		void load(std::vector<WordTranslation> new_translations);
		void clear();

		std::string_view operator()() const;
		std::string_view get_random_translation() const;

	private:
		std::size_t get_max_random_range() const;
		std::string_view get_translation(std::size_t weighted_index) const;

	private:
		std::vector<WordTranslation> _translation;
};
