#pragma once

#include <string_view>

#include <TranslatorCallable.hpp>
#include <StaticMap.hpp>
#include <WordTranslations.hpp>

namespace YololTranslator
{

namespace generated
{

#ifdef STUB_GENERATED

constexpr std::size_t WORD_TRANSLATOR_SIZE = 5;

constexpr StaticMap<std::string_view, TranslatorCallable, WORD_TRANSLATOR_SIZE> load_word_translator_map()
{
	StaticMap<std::string_view, TranslatorCallable, WORD_TRANSLATOR_SIZE> map
	{
		// Keys
		{
			"test",
			"salut",
			"bonjour",
			"hey",
			"rien"
		},
		// Values
		{
			createWordTranslationContainer(WordTranslation{ 1, "taist" }),
			createWordTranslationContainer(WordTranslation{ 1, "slt" }, WordTranslation{ 1, "salu" }),
			createWordTranslationContainer(WordTranslation{ 1, "bjr" }, WordTranslation{ 1, "bonjoure" }),
			createWordTranslationContainer(WordTranslation{ 1, "heyy" }, WordTranslation{ 1, "heyyy" }, WordTranslation{ 1, "heyyyy" }),
			createWordTranslationContainer(WordTranslation{ 1, "ri1" }, WordTranslation{ 1, "ryen" }, WordTranslation{ 1, "ry1" }, WordTranslation{ 1, "rill1" })
		}
	};
	return map;
}

#endif

} // namespace generated


} // namespace YololTranslator
