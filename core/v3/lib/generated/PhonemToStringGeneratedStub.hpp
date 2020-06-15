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
			PhonemUniqueTranslation
			(
				Phonem::aa,
				PhonemEquivalent{ "a", 1, true, true, true }
			),
			PhonemUniqueTranslation
			(
				Phonem::ss,
				PhonemEquivalent{ "s", 15, true, false, false },
				PhonemEquivalent{ "ç", 2, true, true, true },
				PhonemEquivalent{ "ss", 10, false, true, true }
			),
			PhonemUniqueTranslation
			(
				Phonem::mm,
				PhonemEquivalent{ "m", 10, true, true, true },
				PhonemEquivalent{ "mm", 10, false, true, false }
			),
			PhonemUniqueTranslation
			(
				Phonem::ai,
				PhonemEquivalent{ "ai", 10, true, true, true },
				PhonemEquivalent{ "è", 10, true, true, true },
				PhonemEquivalent{ "ê", 10, true, true, true }
			),
			PhonemCompositionTranslation
			{
				PhonemList(Phonem::au, Phonem::aa),
				1,
				{
					PhonemEquivalent{ "wa", 15, true, true, true }
				}
			}	
		}
	};
	return map;
}

#endif

} // namespace generated


} // namespace YololTranslator
