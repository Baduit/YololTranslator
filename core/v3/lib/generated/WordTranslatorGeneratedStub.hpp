#pragma once

#include <string_view>

#include <TranslatorCallable.hpp>
#include <StaticMap.hpp>
#include <WordTranslations.hpp>

namespace YololTranslator
{

namespace generated
{

constexpr std::size_t WORD_TRANSLATOR_SIZE = 5;

inline StaticMap<TranslatorCallable, WORD_TRANSLATOR_SIZE> load_word_translator_map()
{
	StaticMap<TranslatorCallable, WORD_TRANSLATOR_SIZE> map
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
				WordTranslationContainer<1>
					{
						{ WordTranslation{ 1, "taist" } }
					},
				WordTranslationContainer<2>
					{
						{ WordTranslation{ 1, "slt" }, WordTranslation{ 1, "salu" } }
					},
				WordTranslationContainer<2>
					{
						{ WordTranslation{ 1, "bjr" }, WordTranslation{ 1, "bonjoure" } }
					},
				WordTranslationContainer<3>
					{
						{ WordTranslation{ 1, "heyy" }, WordTranslation{ 1, "heyyy" }, WordTranslation{ 1, "heyyyy" } }
					},
				WordTranslationContainer<4>
					{
						{ WordTranslation{ 1, "ri1" }, WordTranslation{ 1, "ryen" }, WordTranslation{ 1, "ry1" }, WordTranslation{ 1, "rill1" } }
					}
			}
		};
	return map;
}

} // namespace generated


} // namespace YololTranslator
