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
		std::size_t	random(std::size_t max_value_included);

	private:
		std::random_device 					_rd;
		std::mt19937						_mt;

		WordsPhonemDictionnary	_dict;
		// later word to word dictionnary
};