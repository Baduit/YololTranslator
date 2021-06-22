#pragma once

#include <string>
#include <string_view>

#include <WordToWord/WordTranslator.hpp>
#include <Phonem/WordToPhonems.hpp>
#include <Phonem/PhonemListToString.hpp>


class Translator
{
	public:
		Translator(std::string_view phonems_list_filename, std::string_view words_phonem_filename, std::string_view word_dict_filename);

		std::string	operator()(std::string_view sentence_to_translate) const;
		std::string translate_word(std::string_view word_to_translate) const;

	private:
		WordTranslator _word_translator;
		WordToPhonems _word_to_phonem;
		PhonemListToString _phonem_list_to_string;
};

