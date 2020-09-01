#pragma once

#include <map>
#include <vector>
#include <string_view>
#include <stdexcept>
#include <algorithm>

#include <Phonem/Phonem.hpp>
#include <Phonem/PhonemTranslation.hpp>
#include <Phonem/TranslationState.hpp>
#include <Phonem/EquivalentChooser.hpp>


class PhonemListToString
{
	public:
		PhonemListToString() = default;

		std::string	operator()(const std::vector<Phonem>& phonem_list);

		void load(std::string_view filename);
		void clear();

	private:
		std::vector<const PhonemTranslation*> get_matches(Phonem p) const;

		template <typename It>
		std::string_view get_possible_equivalent(It& begin, It end, TranslationState state)
		{
			Phonem first_phonem = *begin;
			auto phonem_translation_list = get_matches(first_phonem);
			if (phonem_translation_list.empty())
				throw std::runtime_error("Phonem not found in the map of PhonemTranslation by Phonem. " + std::to_string(static_cast<int>(first_phonem)));

			
			// Sort the array so I can simply look up on it later
			std::sort(phonem_translation_list.begin(), phonem_translation_list.end(),
				[&](const auto* a, const auto* b)
				{
					return a->get_nb_phonems() > b->get_nb_phonems();
				});

			for (auto* phonem_translation: phonem_translation_list) // The pointer can't be NULL
			{
				if (phonem_translation->match_phonems(begin, end))
				{
					begin += static_cast<int>(phonem_translation->get_nb_phonems());
					return EquivalentChooser(phonem_translation->get_equivalents())(state);
				}
			}

			throw std::runtime_error("Phonem not usable in the map of PhonemTranslation by Phonem. " + std::to_string(static_cast<int>(first_phonem)));
		}

		template <typename It>
		TranslationState get_next_translation_state(TranslationState state, It actual, It end)
		{
			switch (state)
			{
				case TranslationState::BEGIN :
				{
					return TranslationState::MIDDLE; 
				}
				case TranslationState::MIDDLE :
				{
					if (actual == end || (actual + 1) == end)
						return TranslationState::END;
					else
						return TranslationState::MIDDLE;
				}
				case TranslationState::END :
				{
					// Throw or log something ? Cuz this is weird
					return TranslationState::END;
				}
			}
			throw std::runtime_error("Who changed the enum without updating updating this.");
		}

	private:
		std::vector<PhonemTranslation> _map;
};
