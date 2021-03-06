#pragma once

#include <Phonem/PhonemTranslation.hpp>
#include <Phonem/TranslationState.hpp>
#include <utilities/Random.hpp>

template <typename ArrayOfEquivalent>
struct EquivalentChooser
{
	public:
		EquivalentChooser(const ArrayOfEquivalent& array):
			_equivalents(array)
		{}

		std::string_view operator()(TranslationState state) const
		{
			return get_random_translation(state);
		}

		std::string_view get_random_translation(TranslationState state) const
		{
			return get_translation(Random::rand(get_max_random_range(state)), state);
		}

	private:
		bool is_equivalent_valid_in_this_state(const PhonemEquivalent& equivalent, TranslationState state) const
		{
			if (state == TranslationState::BEGIN)
			{
				return equivalent.can_begin;
			}
			else if (state == TranslationState::MIDDLE)
			{
				return equivalent.can_middle;
			}
			else // if (state == TranslationState::END)
			{
				return equivalent.can_end;
			}
		}

		std::size_t get_max_random_range(TranslationState state) const noexcept
		{
			std::size_t result = 0;
			for (const auto& e: _equivalents)
			{
				if (is_equivalent_valid_in_this_state(e, state))
					result += e.weight;
			}
			return result;
		}

		std::string_view get_translation(std::size_t weighted_index, TranslationState state) const noexcept
		{
			std::size_t i = 0;
			for (const auto& e: _equivalents)
			{
				if (is_equivalent_valid_in_this_state(e, state))
				{
					i += e.weight;
					if (i >= weighted_index)
						return e.chars;
				}
			}
			return ""; // Should never happen
		}

	private:
		const ArrayOfEquivalent& _equivalents;

};
