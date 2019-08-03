#include <algorithm>
#include <stdexcept>

#include <boost/algorithm/string.hpp>

#include "WordsPhonemDictionnary.hpp"

WordsPhonemDictionnary::WordsPhonemDictionnary(std::string_view filename, const PhonemList& phonems)
{
	load(filename, phonems);
}

void	WordsPhonemDictionnary::load(std::string_view filename, const PhonemList& phonems)
{
	std::ifstream dict_file(filename.data());

	std::string line;
	while (std::getline(dict_file, line))
	{
		std::vector<std::string> splited_line;
		boost::split(splited_line, line, boost::is_any_of(" "));
		if (splited_line.size() > 1)
		{
			std::vector<Phonem> word_as_phonem;
			for (std::size_t i = 1; i < splited_line.size(); ++i)
				if (splited_line[i].size())
					word_as_phonem.push_back(phonems[splited_line[i]]);

			_dict[std::move(splited_line[0])] = std::move(word_as_phonem);
		}
	}
}

const std::vector<Phonem>&	WordsPhonemDictionnary::get_phonems_of(std::string_view word) const
{
	auto key_equals =
		[word](const auto& p)
		{
			return (p.first == word);
		};

	auto it = std::find_if(_dict.cbegin(), _dict.cend(), key_equals);
	if (it == _dict.cend())
		throw std::runtime_error("Word not found: " + std::string(word));
	return it->second;
}

const std::vector<Phonem>&	WordsPhonemDictionnary::operator[](std::string_view word) const
{
	auto key_equals =
		[word](const auto& p)
		{
			return (p.first == word);
		};

	auto it = std::find_if(_dict.cbegin(), _dict.cend(), key_equals);
	if (it == _dict.cend())
		throw std::runtime_error("Word not found: " + std::string(word));
	return it->second;
}