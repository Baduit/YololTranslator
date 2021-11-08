#pragma once

extern "C"
{

typedef struct YololTranslationS
{
	int size;
	char* translation;
} YololTranslation;

void yolol_init(const char* phonems_list_filename, const char* words_phonem_filename, const char* word_dict_filename);

YololTranslation translate(const char* str, int size);
void yolol_free(YololTranslation translation);

void yolol_destroy();

} // extern "C"