#include <algorithm>

#include "Translator.hpp"

Translator::Translator(std::string_view phonems_list_filename, std::string_view words_phonem_filename):
	_mt(_rd()),
	_dict(words_phonem_filename, PhonemList(phonems_list_filename))
{}

std::string	Translator::translate(std::string_view word)
{
	// TODO check a word to word dict 1st

	std::string result;
	PositionCondition actual_pos = PositionCondition::BEGIN;

	const auto& phonems = _dict.get_phonems_of(word);
	for (const auto& phonem: phonems)
	{
		const auto& chars_equivalents = phonem.get_chars_equivalents();
		if (chars_equivalents.size() == 1)
		{
			result += chars_equivalents.front().chars;
		}
		else
		{
			std::vector<const CharsEquivalent*> possible_eq;
			for (const auto& eq: chars_equivalents)
			{
				if (eq.position_conditions.empty() ||
					std::find(eq.position_conditions.cbegin(), eq.position_conditions.end(), actual_pos) != eq.position_conditions.cend())
				{
					possible_eq.push_back(&eq);
				}
			}
			// ignore weight for now
			result += possible_eq[random(possible_eq.size() - 1)]->chars;
		}
	}

	return result;;
}

std::size_t	Translator::random(std::size_t max_value_included)
{
	std::uniform_int_distribution<std::size_t> dist(0, max_value_included);
	return dist(_mt);
}