#pragma once

#include <functional>
#include <optional>

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

		constexpr const std::optional<std::string_view>	operator[](std::string_view word)
		{
			const TranslatorCallable* c = _map[word];
			if (c)
			{
				return (*c)();
			}

			return {};
		}

	private:
		StaticMap<TranslatorCallable, generated::WORD_TRANSLATOR_SIZE> _map;
};
	
} // namespace YololTranslator
