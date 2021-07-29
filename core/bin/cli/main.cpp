#include <iostream>

#include <Translator.hpp>
#include <Isaarg.hpp>

int main(int argc, char** argv)
{
	Isaarg::Args args(argc, argv);

	auto word_to_phonem = args["word_to_phonem"];
	auto word_to_word = args["word_to_word"];
	auto phonems_to_chars = args["phonems_to_chars"];

	if (!word_to_phonem || !word_to_word || !phonems_to_chars)
	{
		std::cout << "Needs args --word_to_phonem <path> --word_to_word <path> --phonems_to_chars <path>" << std::endl;
		return 1;
	}

	Translator translator(*phonems_to_chars, *word_to_phonem, *word_to_word);
	
	std::string line;
	while (std::getline(std::cin, line, '\n'))
	{
		try
		{
			std::cout << translator(line) << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "Invalid input: " << e.what() << std::endl;
		}
	}
}