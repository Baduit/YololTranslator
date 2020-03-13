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

StaticMap<TranslatorCallable, WORD_TRANSLATOR_SIZE> load_word_translator_map()
{
	StaticMap<TranslatorCallable, WORD_TRANSLATOR_SIZE> map
		{
			// Keys
			{
				"",
				"",
				"",
				"",
				""
			},
			// Values
			{
				WordTranslationContainer<1>
					{
						{ WordTranslation{ 1, "" } }
					},
				WordTranslationContainer<2>
					{
						{ WordTranslation{ 1, "" }, WordTranslation{ 1, "" } }
					},
				WordTranslationContainer<2>
					{
						{ WordTranslation{ 1, "" }, WordTranslation{ 1, "" } }
					},
				WordTranslationContainer<3>
					{
						{ WordTranslation{ 1, "" }, WordTranslation{ 1, "" }, WordTranslation{ 1, "" } }
					},
				WordTranslationContainer<4>
					{
						{ WordTranslation{ 1, "" }, WordTranslation{ 1, "" }, WordTranslation{ 1, "" }, WordTranslation{ 1, "" } }
					}
			}
		};
	return map;
}

} // namespace generated


} // namespace YololTranslator
