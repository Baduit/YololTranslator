#include <cstring>
#include <cctype>

#include <SharedLibInterface.hpp>
#include <Split.hpp>

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

YololResult init_translator(std::string_view phonems_list_filename, std::string_view words_phonem_filename, std::string_view word_dict_filename)
{
	try
	{
		translator.emplace(phonems_list_filename, words_phonem_filename, word_dict_filename);
		return YOLOL_SUCCESS;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception in init_translator: " << e.what() << std::endl;
		return YOLOL_FAILURE;
	}
}

char* translate_translator(std::string_view input)
{
	try
	{
		auto lower_case_input = to_lower(input);
		std::string output;
		auto words = tokenize(lower_case_input, {" ", ";", ",", ".", "\t", "\n", "!", "?", ":", "-"});
		for (const auto w: words)
		{
			if (w.type == Token::Type::WORD)
			{
				try
				{
					output += translator->translate(w.value);
				}
				catch (std::runtime_error& e) // to handle unknown words, i should make designated exception or handle it in the translator or better use optional
				{
					output += w.value;
				}
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
		output += "\n";

		return strdup(output.c_str());
	}
	catch (std::exception& e)
	{
		return strdup(e.what());
	}
}

extern "C"
{

int	init(const char* phonems_list_filename, const char* words_phonem_filename, const char* word_dict_filename)
{
	return init_translator(phonems_list_filename, words_phonem_filename, word_dict_filename);
}

// do not forget to delete output ptr
char*	translate(const char* input)
{
	return translate_translator(input);
}

void				delete_string(char *str)
{
	free(str);
}

void			destroy()
{
	translator.reset();
}

}