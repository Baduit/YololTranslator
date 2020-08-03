#pragma once

#include <optional>
#include <string_view>
#include <map>
#include <algorithm>

#include <WordToWord/WordTranslation.hpp>
#include <JsonUnserializer.hpp>

#include <utilities/File.hpp>

class WordToWordTranslator
{
	public:
		WordToWordTranslator() = default;

		WordToWordTranslator(const WordToWordTranslator&) = default;
		WordToWordTranslator& operator=(const WordToWordTranslator&) = default;

		WordToWordTranslator(WordToWordTranslator&&) = default;
		WordToWordTranslator& operator=(WordToWordTranslator&&) = default;

		void load(std::string_view filename)
		{
			
		}

		const std::optional<std::string_view>	operator[](std::string_view word)
		{
			auto it = std::find_if(_map.begin(), _map.end(),
				[word](const auto& pair)
				{
					return word == pair.first;
				});
			if (it != _map.end())
				return (it->second)();
			else
				return {};
		} 

	private:
		std::map<std::string, WordTranslationContainer> _map;
};