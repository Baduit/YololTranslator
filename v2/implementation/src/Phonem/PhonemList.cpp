#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "PhonemList.hpp"

PhonemList::PhonemList(std::string_view filename)
{
	load_from_file(filename);
}

void	PhonemList::load_from_file(std::string_view filename)
{
		std::ifstream dict_file(filename.data());
		std::string file_content;


		// this could be optimized, but i will not be called often
		std::string line;
		while (std::getline(dict_file, line))
		{
			file_content += line;
		}

		json json_content = json::parse(file_content);
		for (const auto& p: json_content["phonems"])
		{
			std::string code = p["code"].get<std::string>();

			std::vector<CharsEquivalent> chars_eq;
			for (const auto& cs: p["equivalents"])
			{
				CharsEquivalent eq;
				eq.chars = cs["chars"].get<std::string>();
				// position see later
				eq.weight = cs["weight"].get<int>();
				chars_eq.push_back(std::move(eq));
			}

			_phonems.push_back(Phonem(std::move(code), std::move(chars_eq)));
		}
}

const std::vector<Phonem>&	PhonemList::get_phonems() const
{
	return _phonems;
}

const Phonem&	PhonemList::operator[] (std::string_view code) const
{
	for (const auto& p: _phonems)
	{
		if (p.get_code() == code)
			return p;
	}

	throw std::runtime_error("Phonem not found!");
}