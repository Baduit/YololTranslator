#pragma once

#include <functional>

#include <StaticMap.hpp>
#include <WordTranslations.hpp>

#include <generated/WordTranslatorGeneratedStub.hpp>

namespace YololTranslator
{

class WordTranslator
{
	public:
		WordTranslator():
			_map(generated::load_word_translator_map())
		{}

	private:
		StaticMap<TranslatorCallable, generated::WORD_TRANSLATOR_SIZE> _map;
};
	
} // namespace YololTranslator
