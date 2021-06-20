#include <algorithm>

#include <Translator.hpp>
#include <utilities/Split.hpp>

namespace
{

std::string to_lower(std::string_view str)
{
	std::string result;
	result.reserve(str.size());

	for (auto c: str)
		result += static_cast<char>(tolower(c));

	return result;
}

}

Translator::Translator(std::string_view phonems_list_filename, std::string_view words_phonem_filename, std::string_view word_dict_filename)
{
	_phonem_list_to_string.load(phonems_list_filename);
	_word_to_phonem.load(words_phonem_filename);
	_word_translator.load(word_dict_filename);
}

std::string Translator::operator()(std::string_view sentence)
{
	auto lower_case_sentence = to_lower(sentence);
	std::string output;
	bool in_tag = false; 
	auto words = tokenize(lower_case_sentence, {" ", ";", ",", ".", "\t", "\n", "!", "?", ":", "-", "<@", ">"});
	for (const auto w: words)
	{
		if (in_tag)
		{
			if (w.type == Token::Type::DELIMiTER && w.value == ">")
				in_tag = false;
			output += w.value;
		}
		else
		{
			if (w.type == Token::Type::DELIMiTER && w.value == "<@")
			{
				in_tag = true;
				output += w.value;
			}
			else if (w.type == Token::Type::WORD)
			{
				output += translate_word(w.value);
			}
			else // if is token
			{
				if (w.value == "?" || w.value == "!")
				{
					output += w.value;
					output += w.value;
				}
				else if (w.value == "\n")
				{
					output += w.value;
				}
				else
				{
					output += " ";
				}
			}
		}
	}

	return output;
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