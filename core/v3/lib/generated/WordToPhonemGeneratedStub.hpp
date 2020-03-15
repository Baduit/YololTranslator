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

constexpr std::size_t WORD_TO_PHONEM_SIZE = 2;

constexpr StaticMap<PhonemList, WORD_TO_PHONEM_SIZE> load_word_to_phonems_map()
{
	StaticMap<PhonemList, generated::WORD_TO_PHONEM_SIZE> map
		{
			// Keys
			{
				"assez",
				"moi"
			},
			// Values
			{
				
			}
		};
	return map;
}

#endif

} // namespace generated


} // namespace YololTranslator
