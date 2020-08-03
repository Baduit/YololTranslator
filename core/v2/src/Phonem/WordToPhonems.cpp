#include <fstream>
#include <algorithm>
#include <iostream>

#include <Phonem/WordToPhonems.hpp>

#include <external/magic_enum/magic_enum.hpp>
#include <utilities/Split.hpp>

void WordToPhonems::load(std::string_view filename)
{
	std::ifstream file(filename.data());
	std::string line;
	int actual_line = 1;
	while (std::getline(file, line))
	{
		if (line.back() == '\r')
			line.pop_back();

		auto strings = split(line, {" "});
		if (strings.size() <= 1)
			throw std::runtime_error("Error while parsing line " + std::to_string(actual_line));
		
		std::vector<Phonem> phonems;
		phonems.reserve(strings.size() - 1);
		for (auto it = strings.begin() + 1; it != strings.end(); ++it)
			phonems.push_back(*magic_enum::enum_cast<Phonem>(*it));
		_map[std::string(strings[0])] = phonems;

		++actual_line;
	}
}

void WordToPhonems::clear()
{
	_map.clear();
}

const std::vector<Phonem>*	WordToPhonems::operator[](std::string_view word)
{
	auto it = std::find_if(_map.begin(), _map.end(),
		[word](const auto& pair)
		{
			return word == pair.first;
		});
	if (it != _map.end())
		return &(it->second);
	else
		return nullptr;
}