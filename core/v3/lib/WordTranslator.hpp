#pragma once

#include <functional>
#include <optional>

#include <StaticMap.hpp>
#include <WordTranslations.hpp>

#ifdef STUB_GENERATED
	#include <generated/WordTranslatorGeneratedStub.hpp>
#else
	// TODO
#endif

namespace YololTranslator
{

class WordTranslator
{
	public:
		constexpr WordTranslator():
			_map(generated::load_word_translator_map())
		{}

		const std::optional<std::string_view>	operator[](std::string_view word)
		{
			const TranslatorCallable* c = _map[word];
			if (c)
			{
				return (*c)();
			}

			return {};
		}

	private:
		StaticMap<std::string_view, TranslatorCallable, generated::WORD_TRANSLATOR_SIZE> _map;
};
	
} // namespace YololTranslator
