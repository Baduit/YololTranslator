#include <optional>
#include <string_view>
#include <cstring>

#include <SharedInterface.hpp>
#include <Translator.hpp>



static std::optional<Translator> translator;

void yolol_init(const char* phonems_list_filename, const char* words_phonem_filename, const char* word_dict_filename)
{
	translator.emplace(phonems_list_filename, words_phonem_filename, word_dict_filename);
}

YololTranslation translate(const char* str, int size)
{
	auto translation = (*translator)(std::string_view(str, static_cast<std::size_t>(size)));
	YololTranslation result;
	result.size = static_cast<int>(translation.size());
	#if defined(_WIN32)
		result.translation = _strdup(translation.data());
	#else
		result.translation = strdup(translation.data());
	#endif
	return result;
}

void yolol_free(YololTranslation translation)
{
	free(reinterpret_cast<void*>(translation.translation));
}

void yolol_destroy()
{
	translator.reset();
}
