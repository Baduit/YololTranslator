#include <iostream>

#include <Translator.hpp>

int main()
{
	std::cout << "Hello, World!" << std::endl;
	YololTranslator::Translator translator;
	/*for (int i = 0; i < 5; ++i)
		std::cout << translator.translate_word("salut") << std::endl;
	for (int i = 0; i < 5; ++i)
		std::cout << translator.translate_word("rien") << std::endl;*/

	for (int i = 0; i < 5; ++i)
		std::cout << translator.translate_word("assez") << std::endl;		
	for (int i = 0; i < 5; ++i)
		std::cout << translator.translate_word("moi") << std::endl;				
}