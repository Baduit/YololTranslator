#include <cstring>
#include <cctype>
#include <iostream>

#include <SharedLibInterface.hpp>

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
		return strdup((*translator)(input).c_str());
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