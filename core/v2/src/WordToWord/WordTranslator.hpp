#pragma once

#include <optional>
#include <map>
#include <string>

#include <WordToWord/WordTranslations.hpp>



class WordTranslator
{
	public:
		WordTranslator() = default;

		void load(std::string_view filename);
		void clear();

		const std::optional<std::string_view>	operator[](std::string_view word);

	private:
		std::map<std::string, WordTranslationContainer> _map;
};
