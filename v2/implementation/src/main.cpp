#include <iostream>

#include "PhonemList.hpp"

int main()
{
	std::cout << "Yo man!" << std::endl;

	PhonemList test("../assets/french_dico.json");
	const auto& phonem_ss = test["ss"];
	std::cout << phonem_ss.get_chars_equivalents()[1].chars << std::endl;

	std::cout << "Bye man!" << std::endl;

}