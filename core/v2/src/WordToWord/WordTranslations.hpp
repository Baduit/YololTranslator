#pragma once

#include <vector>
#include <string>
#include <string_view>

struct WordTranslation final
{
	bool operator==(const WordTranslation&) const = default;
	auto operator<=>(const WordTranslation&) const = default;

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

		bool operator==(const WordTranslationContainer&) const = default;
		auto operator<=>(const WordTranslationContainer&) const = default;

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
