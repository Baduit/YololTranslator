#pragma once

#include <map>
#include <string>
#include <vector>

#include <Phonem/Phonem.hpp>

class WordToPhonems
{
	public:
		WordToPhonems() = default;

		void load(std::string_view filename);
		void clear();

		const std::vector<Phonem>*	operator[](std::string_view word);

	private:
		std::map<std::string, std::vector<Phonem>> _map;
};
