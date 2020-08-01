#pragma once

#include <optional>
#include <string>

#include <Translator.hpp>

extern "C"
{
// Common definitions but C compatible
enum YololResult: int
{
	YOLOL_FAILURE = 0,
	YOLOL_SUCCESS = 1,
};

}


// C++ definitions
inline std::optional<Translator> translator;

YololResult init_translator(std::string_view phonems_list_filename, std::string_view words_phonem_filename, std::string_view word_dict_filename);

// do not forget to delete output ptr
char* translate_translator(std::string_view input);


// C interface definition
extern "C"
{

int		init(const char* phonems_list_filename, const char* words_phonem_filename, const char* word_dict_filename);

// do not forget to delete output ptr
char*	translate(const char* input);

void	delete_string(char *str);

void	destroy();

}