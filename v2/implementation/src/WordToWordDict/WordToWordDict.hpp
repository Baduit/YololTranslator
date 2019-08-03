#pragma once

#include <string_view>
#include <string>
#include <map>
#include <vector>

#include "CharsEquivalent.hpp"

class WordToWordDict
{
	using WordDict = std::map<std::string, std::vector<CharsEquivalent>>;

	public:
		WordToWordDict(std::string_view filename);

		WordToWordDict(const WordToWordDict&) = delete;
		WordToWordDict& operator=(const WordToWordDict&) = delete;

		WordToWordDict(WordToWordDict&&) = default;
		WordToWordDict& operator=(WordToWordDict&&) = default;

		void	load(std::string_view filename);

		// Return a pointer because optional on reference need a lot of boiler plate
		// And i prefer to keep exception for exceptional behavior, not possible normal behavior
		const std::vector<CharsEquivalent>*		operator[](std::string_view word) const;

	private:
		WordDict	_word_dict;
};