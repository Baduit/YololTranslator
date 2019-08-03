#include <fstream>
#include <algorithm>

#include <nlohmann/json.hpp>

#include "WordToWordDict.hpp"

WordToWordDict::WordToWordDict(std::string_view filename)
{
	load(filename);
}

void	WordToWordDict::load(std::string_view filename)
{
	_word_dict.clear();

	std::ifstream dict_file(filename.data());
	std::string file_content;


	// this could be optimized, but it will not be called often
	std::string line;
	while (std::getline(dict_file, line))
	{
		file_content += line;
	}

	json json_content = json::parse(file_content);
	for (const auto& w: json_content.at("words"))
	{
		std::string word = w.at("word").get<std::string>();

		std::vector<CharsEquivalent> str_equivalents;
		for (const auto& str_eq: w.at("equivalents"))
		{
			CharsEquivalent eq;

			eq.chars = str_eq.at("chars").get<std::string>();
			eq.weight = str_eq.at("weight").get<int>();

			str_equivalents.push_back(std::move(eq));
		}

		_word_dict[std::move(word)] = std::move(str_equivalents);
	}
}

const std::vector<CharsEquivalent>*		WordToWordDict::operator[](std::string_view word) const
{
	// I really need to make a MapAdaptor to be able to use any equalality comparable type to search in a map ([], at, find)
	for (const auto& [k, v]: _word_dict)
	{
		if (k == word)
			return &v;
	}
	return nullptr;
}