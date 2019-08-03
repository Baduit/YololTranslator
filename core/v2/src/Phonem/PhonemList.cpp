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
		_phonems.clear();

		std::ifstream dict_file(filename.data());
		std::string file_content;


		// this could be optimized, but it will not be called often
		std::string line;
		while (std::getline(dict_file, line))
		{
			file_content += line;
		}

		json json_content = json::parse(file_content);
		for (const auto& p: json_content.at("phonems"))
		{
			std::string code = p.at("code").get<std::string>();

			std::vector<CharsEquivalent> chars_eq;
			for (const auto& cs: p.at("equivalents"))
			{
				CharsEquivalent eq;

				eq.chars = cs.at("chars").get<std::string>();
				eq.weight = cs.at("weight").get<int>();

				auto pos_cond = cs.find("pos");
				if (pos_cond != cs.end())
				{
					if (pos_cond->is_array())
						for (const auto& pos: *pos_cond)
							eq.position_conditions.push_back(*(position_condition_from_string(pos.get<std::string_view>())));
					else
						eq.position_conditions.push_back(*(position_condition_from_string(pos_cond->get<std::string_view>())));
				}
				
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

	throw std::runtime_error("Phonem not found: " + std::string(code));
}