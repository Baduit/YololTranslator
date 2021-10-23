#include <utilities/Isaarg.hpp>

#include <WSService.hpp>

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
	WSService service(translator, 4577);
}