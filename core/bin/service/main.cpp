#include <chrono>

#include <utilities/Isaarg.hpp>
#include <thuto/utils/Sleeper.hpp>

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

	for (;;)
	{
		try
		{
			Translator translator(*phonems_to_chars, *word_to_phonem, *word_to_word);
			WSService service(translator, 4577);
		}
		catch (...)
		{
			// I'm ugly, I'll ignore, I don't have a real logging stuff so, it will just restart the service after anyway
		}

		{
			using namespace std::chrono_literals;
			thuto::Sleeper sleeper;
			sleeper.sleep(30s);
		}
	}
}