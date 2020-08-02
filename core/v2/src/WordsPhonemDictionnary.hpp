#pragma once

#include <string_view>
#include <string>
#include <vector>
#include <map>
#include <fstream>

#include <Phonem.hpp>
#include <PhonemList.hpp>

class WordsPhonemDictionnary
{
	public:
		WordsPhonemDictionnary(std::string_view filename, const PhonemList& phonems);

		WordsPhonemDictionnary(const WordsPhonemDictionnary&) = delete;
		WordsPhonemDictionnary& operator=(const WordsPhonemDictionnary&) = delete;

		WordsPhonemDictionnary(WordsPhonemDictionnary&&) = default;
		WordsPhonemDictionnary& operator=(WordsPhonemDictionnary&&) = default;

		void	load(std::string_view filename, const PhonemList& phonems);

		const std::vector<Phonem>*	get_phonems_of(std::string_view word) const;

		const std::vector<Phonem>*	operator[](std::string_view word) const;

	private:
		std::map<std::string, std::vector<Phonem>>	_dict;
};