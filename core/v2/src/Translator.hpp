#pragma once

#include <string>
#include <string_view>
#include <optional>
#include <random>

#include <WordsPhonemDictionnary.hpp>
#include <WordToWordDict.hpp>
#include <PhonemList.hpp>
#include <PhonemCompositionList.hpp>

class Translator
{
	public:
		Translator(std::string_view phonems_list_filename, std::string_view words_phonem_filename, std::string_view word_dict_filename);

		Translator(const Translator&) = delete;
		Translator& operator=(const Translator&) = delete;

		Translator(Translator&&) = default;
		Translator& operator=(Translator&&) = default;

		std::string operator()(std::string_view sentence);

		std::string operator[](std::string_view word);
		std::string	translate_word(std::string_view word);


	private:
		template<typename ConstIt>
		void	update_word_position(PositionCondition& pos, ConstIt actual, ConstIt end) const
		{
			if (pos == PositionCondition::BEGIN)
			{
				pos = PositionCondition::MIDDLE;
			}
			else if (pos == PositionCondition::MIDDLE)
			{
				if ((actual + 1) == end)
				{
					pos = PositionCondition::END;
				}
			}
			else // if (pos == PositionCondition::END)
			{
				throw std::runtime_error("It should not be happening, position already to end");
			}
		}

		// The handling of the weight is not optimized but it is simple and it work and can be used in a generic way in this project
		std::vector<const CharsEquivalent*>	create_possible_equivalents(const std::vector<CharsEquivalent>& char_eq) const;
		std::vector<const CharsEquivalent*>	create_possible_equivalents(const std::vector<CharsEquivalent>& char_eq, PositionCondition actual_pos) const;
		std::size_t							random(std::size_t max_value_included);
		const CharsEquivalent&				get_random_char_equivalent(std::vector<const CharsEquivalent*> possible_eq);

	private:
		std::random_device 					_rd;
		std::mt19937						_mt;

		WordsPhonemDictionnary	_phonem_dict;
		PhonemCompositionList	_phonem_composition_list;
		WordToWordDict			_word_dict;
};