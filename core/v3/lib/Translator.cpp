#include "Translator.hpp"

namespace YololTranslator
{

std::string	Translator::translate(std::string_view sentence_to_translate)
{
	(void) sentence_to_translate;
	return "";
}

std::string Translator::translate_word(std::string_view word_to_translate)
{

	if (auto opt_translation = _word_translator[word_to_translate]; opt_translation)
		return std::string(*opt_translation);
	else if (auto opt_phonems = _word_to_phonem[word_to_translate]; opt_phonems)
		return _phonem_list_to_string(*opt_phonems);
	else
		return std::string(word_to_translate);
}

} // namespace YololTranslator
