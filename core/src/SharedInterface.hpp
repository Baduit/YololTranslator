#pragma once

extern "C"
{

typedef struct YololTranslationS
{
	int size;
	char* translation;
} YololTranslation;

void yolol_init(const char* phonems_to_chars, const char* word_to_phonem, const char* word_to_word);

YololTranslation yolol_translate(const char* str, int size);
void yolol_free(YololTranslation translation);

void yolol_destroy();

} // extern "C"