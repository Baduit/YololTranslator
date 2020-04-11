#pragma once

#include <StaticMap.hpp>
#include <PhonemList.hpp>

#ifdef STUB_GENERATED
	#include <generated/WordToPhonemGeneratedStub.hpp>
#else
	// TODO
#endif

namespace YololTranslator
{

class WordToPhonems
{
	public:
		constexpr WordToPhonems():
			_map(generated::load_word_to_phonems_map())
		{}

		const PhonemList*	operator[](std::string_view word)
		{
			return _map[word];
		}

	private:
		StaticMap<std::string_view, PhonemList, generated::WORD_TO_PHONEM_SIZE> _map;
};

} // namespace YololTranslator
