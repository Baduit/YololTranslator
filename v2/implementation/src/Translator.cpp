#include <algorithm>

#include "Translator.hpp"

Translator::Translator(std::string_view phonems_list_filename, std::string_view words_phonem_filename, std::string_view word_dict_filename):
	_mt(_rd()),
	_phonem_dict(words_phonem_filename, PhonemList(phonems_list_filename)),
	_word_dict(word_dict_filename)
{}

std::string	Translator::translate(std::string_view word)
{
	if (auto* word_translation = _word_dict[word]; word_translation)
	{
		return get_random_char_equivalent(create_possible_equivalents(*word_translation));
	}

	// TODO phonem composition

	std::string result;
	PositionCondition actual_pos = PositionCondition::BEGIN;

	const auto& phonems = _phonem_dict[word];
	for (auto phonem = phonems.cbegin(); phonem != phonems.cend(); ++phonem)
	{
		const auto& chars_equivalents = phonem->get_chars_equivalents();
		if (chars_equivalents.size() == 1)
		{
			result += chars_equivalents.front().chars;
		}
		else
		{
			result += get_random_char_equivalent(create_possible_equivalents(chars_equivalents, actual_pos));
		}
		update_word_position(actual_pos, phonem, phonems.cend());
	}

	return result;
}

std::vector<const CharsEquivalent*>	Translator::create_possible_equivalents(const std::vector<CharsEquivalent>& char_eq) const
{
	std::vector<const CharsEquivalent*> possible_eq;
	for (const auto& eq: char_eq)
	{
		for (int i = 0; i < eq.weight; ++i)
			possible_eq.push_back(&eq);
	}
	return possible_eq;
}

std::vector<const CharsEquivalent*>	Translator::create_possible_equivalents(const std::vector<CharsEquivalent>& char_eq, PositionCondition actual_pos) const
{
	std::vector<const CharsEquivalent*> possible_eq;
	for (const auto& eq: char_eq)
	{
		if (eq.position_conditions.empty() ||
			std::find(eq.position_conditions.cbegin(), eq.position_conditions.end(), actual_pos) != eq.position_conditions.cend())
		{
			for (int i = 0; i < eq.weight; ++i)
				possible_eq.push_back(&eq);
		}
	}
	return possible_eq;
}

std::size_t	Translator::random(std::size_t max_value_included)
{
	std::uniform_int_distribution<std::size_t> dist(0, max_value_included);
	return dist(_mt);
}

std::string	Translator::get_random_char_equivalent(std::vector<const CharsEquivalent*> possible_eq)
{
	if (possible_eq.empty())
		throw std::runtime_error("Empty chars equivalents in the Translator!");
	return possible_eq[random(possible_eq.size() - 1)]->chars;
}