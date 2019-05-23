#include <iostream>
#include <fstream>
#include <set>

std::set<std::string>	fill_set(const char* filename)
{
	std::set<std::string> phonems;
	std::ifstream file(filename);

	std::string line;
	while (std::getline(file, line))
	{
		bool first_word = true;
		int begin = -1;
		for (uint i = 0; i < line.size(); ++i)
		{
			if (line[i] == ' ')
			{
				if (begin != -1)
				{
					if (!first_word)
						phonems.insert(line.substr(begin, i - begin));
					else
						first_word = false;
					begin = -1;
				}
			}
			else
			{
				if (begin == -1)
					begin = i;
			}
		}
	}
	return phonems;
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Please give me a file to eat, i'm hungry." << std::endl;
		return 0;
	}

	auto result = fill_set(argv[1]);
	//std::cout << result.size() << std::endl;
	for (const auto& phonem: result)
		std::cout << phonem << std::endl;
}