#include <iostream>

#include "Translator.hpp"

int main(int argc, char** argv)
{
	std::cout << "Yo man!" << std::endl;

	Translator translator("../assets/french_dico.json", "../assets/fr.dict", "../assets/word_to_word_dict_fr.json");
	for (int i = 1; i < argc; ++i)
	{
		std::cout << translator.translate(argv[i]) << " ";
	}
	std::cout << std::endl;

	std::cout << "Bye man!" << std::endl;

}