#include <iostream>
#include <map>
#include <string_view>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "json/json.hpp"

// there are a lot of copies every where and it is not optimized at all, it is slow af

class WordsPhonemDictionnary
{
	public:
		WordsPhonemDictionnary(std::string_view filename)
		{
			std::ifstream dict_file(filename.data());

			// this could be heavily optimized, but i will only be called at the begin of the program
			std::string line;
			while (std::getline(dict_file, line))
			{
				std::vector<std::string> phonems;
				boost::split(phonems, line, boost::is_any_of(" "));
				if (!phonems.empty())
				{
					_dict[phonems[0]] = std::vector<std::string>(std::next(phonems.begin()), phonems.end());
				}
			}
		}

		std::vector<std::string>	get_phonems_of(const std::string& word)
		{
			return _dict[word];
		}

	private:
		std::map<std::string, std::vector<std::string>>	_dict;
};

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v)
{
	for (const auto& i: v)
		os << i << " ";
	return os;
}

struct Phonem
{
	std::string					code;
	std::vector<std::string>	chars;
};

class PhonemsCharsDictionnary
{
	public:
		PhonemsCharsDictionnary(std::string_view filename)
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

				std::vector<std::string> chars;
				for (const auto& cs: p["equivalents"])
					chars.push_back(cs["chars"].get<std::string>());

				_phonems[code] = {code, chars};
			}
		}

		std::string get_chars_of(const std::string& phonem_code)
		{
			Phonem p = _phonems[phonem_code];

			std::string res;

			res = p.chars[0]; // random???

			return res;
		}

	private:
		std::map<std::string, Phonem>	_phonems;
};

int main(int argc, char **argv)
{
	if (argc <= 1)
	{
		std::cout << "Give me a sentence to eat, I'm hungry." << std::endl;
		return 1;
	}

	WordsPhonemDictionnary word_phonem_dictionnary("fr.dict");
	PhonemsCharsDictionnary phonems_dhars_dictionnary("french_dico.json");

	for (int i = 1; i < argc; ++i)
	{
		auto phonems = word_phonem_dictionnary.get_phonems_of(argv[i]);
		std::cout << argv[i] << " => " <<  phonems << std::endl;
		std::cout << "=> ";
		for (const auto& p: phonems)
		{
			std::cout << phonems_dhars_dictionnary.get_chars_of(p);
		}
		std::cout << std::endl << std::endl;;
	}
}