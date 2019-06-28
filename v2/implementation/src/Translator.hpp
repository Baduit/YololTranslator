#pragma once

#include <string>
#include <string_view>
#include <optional>
#include <random>

#include "WordsPhonemDictionnary.hpp"
#include "PhonemList.hpp"

class Translator
{
	public:
		Translator(std::string_view phonems_list_filename, std::string_view words_phonem_filename);

		Translator(const Translator&) = delete;
		Translator& operator=(const Translator&) = delete;

		Translator(Translator&&) = default;
		Translator& operator=(Translator&&) = default;

		std::string	translate(std::string_view word);

	private:
		std::vector<const CharsEquivalent*>	create_possible_equivalents(const std::vector<CharsEquivalent>& char_eq, PositionCondition actual_pos) const;

		std::size_t	random(std::size_t max_value_included);
		std::string	get_random_char_equivalent(std::vector<const CharsEquivalent*> possible_eq);

	private:
		std::random_device 					_rd;
		std::mt19937						_mt;

		WordsPhonemDictionnary	_dict;
		// later word to word dictionnary
};