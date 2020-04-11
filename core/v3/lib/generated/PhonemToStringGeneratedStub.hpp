#pragma once

#include <string_view>

#include <TranslatorCallable.hpp>
#include <StaticMap.hpp>
#include <PhonemTranslation.hpp>

namespace YololTranslator
{

namespace generated
{

#ifdef STUB_GENERATED

constexpr std::size_t PHONEM_TO_STRING_SIZE = 5;

constexpr StaticMap<Phonem, PhonemTranslation, PHONEM_TO_STRING_SIZE> load_phonem_to_string_map()
{
	StaticMap<Phonem, PhonemTranslation, PHONEM_TO_STRING_SIZE> map
		{
			// Keys
			{
				Phonem::aa,
				Phonem::ss,
				Phonem::mm,
				Phonem::ai,
				Phonem::au
			},
			// Values
			{
				PhonemTranslation(PhonemUniqueTranslation {}),
				PhonemTranslation(PhonemUniqueTranslation {}),
				PhonemTranslation(PhonemUniqueTranslation {}),
				PhonemTranslation(PhonemUniqueTranslation {}),
				PhonemTranslation(PhonemCompositionTranslation {})
			}
		};
	return map;
}

#endif

} // namespace generated


} // namespace YololTranslator
