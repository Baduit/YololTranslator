#include <algorithm>

#include <Translator.hpp>
#include <utilities/Split.hpp>
#include <utilities/Random.hpp>

namespace
{

std::string to_lower(std::string_view str)
{
	std::string result;
	result.reserve(str.size());

	for (auto c: str)
		result += static_cast<char>(tolower(c));

	return result;
}

}

Translator::Translator(std::string_view phonems_list_filename, std::string_view words_phonem_filename, std::string_view word_dict_filename):
	_mt(_rd()),
	_phonem_dict(words_phonem_filename, PhonemList(phonems_list_filename)),
	_phonem_composition_list(phonems_list_filename),
	_word_dict(word_dict_filename)
{}

std::string Translator::operator()(std::string_view sentence)
{
	auto lower_case_sentence = to_lower(sentence);
	std::string output;
	auto words = tokenize(lower_case_sentence, {" ", ";", ",", ".", "\t", "\n", "!", "?", ":", "-"});
	for (const auto w: words)
	{
		if (w.type == Token::Type::WORD)
		{
			output += translate_word(w.value);
		}
		else // if is token
		{
			if (w.value == "?" || w.value == "!")
			{
				output += w.value;
				output += w.value;
			}
			else if (w.value == "\n")
			{
				output += w.value;
			}
			else
			{
				output += " ";
			}
		}
	}

	return output;
}

std::string Translator::operator[](std::string_view word)
{
	return translate_word(word);
}

std::string	Translator::translate_word(std::string_view word)
{
	if (auto* word_translation = _word_dict[word]; word_translation)
	{
		return get_random_char_equivalent(create_possible_equivalents(*word_translation)).chars;
	}

	std::string result;
	PositionCondition actual_pos = PositionCondition::BEGIN;

	const std::vector<Phonem>* phonems = _phonem_dict[word];
	if (!phonems)
		return std::string(word);

	auto phonem_it = phonems->cbegin();
	while (phonem_it != phonems->cend())
	{
		std::vector<CharsEquivalent> chars_equivalents;
		std::size_t char_eq_composition_size = 1;

		if (const PhonemComposition* pc = _phonem_composition_list(phonem_it, phonems->cend()); pc)
		{
			chars_equivalents = pc->chars_equivalents;		
		}
		else
		{
			throw std::runtime_error("Phonem without a translation : " + std::string(phonem_it->get_code()));
		}

		const auto& tmp_vec = phonem_it->get_chars_equivalents();
		chars_equivalents.insert(chars_equivalents.end(), tmp_vec.cbegin(), tmp_vec.cend());


		if (chars_equivalents.size() == 1)
		{
			const auto& eq = chars_equivalents.front();
			result += eq.chars;
			char_eq_composition_size = eq.composition_size;
		}
		else
		{
			const auto& eq = get_random_char_equivalent(create_possible_equivalents(chars_equivalents, actual_pos));
			result += eq.chars;
			char_eq_composition_size = eq.composition_size;;
		}
		update_word_position(actual_pos, phonem_it, phonems->cend());

		phonem_it += static_cast<int>(char_eq_composition_size);
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

const CharsEquivalent&	Translator::get_random_char_equivalent(std::vector<const CharsEquivalent*> possible_eq)
{
	if (possible_eq.empty())
		throw std::runtime_error("Empty chars equivalents in the Translator!");
	return *(possible_eq[random(possible_eq.size() - 1)]);
}