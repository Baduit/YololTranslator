#pragma once

#include <string_view>

#include <TranslatorCallable.hpp>
#include <StaticMap.hpp>
#include <WordTranslations.hpp>

namespace YololTranslator
{

namespace generated
{

constexpr std::size_t WORD_TRANSLATOR_SIZE = 2;
constexpr StaticMap<std::string_view, TranslatorCallable, WORD_TRANSLATOR_SIZE> load_word_translator_map()
{
	StaticMap<std::string_view, TranslatorCallable, WORD_TRANSLATOR_SIZE> map
	{
		// Keys
		{
			"bonjour",
			"salut"
		},
		// Values
		{
			createWordTranslationContainer(WordTranslation{ 10, "bjr" }, WordTranslation{ 2, "bonjoure" }, WordTranslation{ 2, "bonjourre" }, WordTranslation{ 1, "bongeour" }),
			createWordTranslationContainer(WordTranslation{ 10, "salu" }, WordTranslation{ 5, "slt" })
		}
	};
	return map;
}

}

}
