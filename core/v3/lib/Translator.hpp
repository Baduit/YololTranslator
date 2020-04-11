#pragma once

#define STUB_GENERATED

#include <string>
#include <string_view>

#include <Phonem.hpp>
#include <WordTranslator.hpp>
#include <WordToPhonems.hpp>
#include <PhonemList.hpp>
#include <PhonemListToString.hpp>

namespace YololTranslator
{

class Translator
{
	public:
		std::string	translate(std::string_view sentence_to_translate);
		std::string translate_word(std::string_view word_to_translate);

	private:
		WordTranslator _word_translator;
		WordToPhonems _word_to_phonem;
		PhonemListToString _phonem_list_to_string;
};

} // namespace YololTranslator
