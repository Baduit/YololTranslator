#pragma once

#include <string>
#include <string_view>

#include <Phonem.hpp>
#include <WordTranslator.hpp>

namespace YololTranslator
{

class Translator
{
	public:
		std::string	translate(std::string_view sentence_to_translate);
		std::string translate_word(std::string_view word_to_translate);

	private:
		WordTranslator _word_translator;
};

} // namespace YololTranslator
