#pragma once

#include <algorithm>

#include <PhonemList.hpp>
#include <PhonemTranslation.hpp>

#ifdef STUB_GENERATED
	#include <generated/PhonemToStringGeneratedStub.hpp>
#else
	// TODO
#endif

namespace YololTranslator
{

class PhonemListToString
{
	enum class TranslationState
	{
		BEGIN,
		MIDDLE,
		END
	};


	public:
		constexpr PhonemListToString():
			_map(generated::load_phonem_to_string_map())
		{}

		std::string	operator()(const PhonemList& phonem_list)
		{
			std::string result;

			TranslationState state = TranslationState::BEGIN;
			auto it = phonem_list.phonems.begin();
			auto end = phonem_list.phonems.begin() + phonem_list.size;

			while (it != end)
			{
				result += get_possible_equivalent(it, end, state);
				state = get_next_translation_state(state, it, end);
			}

			return result;;
		}

	private:
		template <typename It>
		std::string_view get_possible_equivalent(It& begin, It end, TranslationState state)
		{
			Phonem first_phonem = *begin;
			auto phonem_translation_list = _map.get_matches(first_phonem);
			if (phonem_translation_list.empty())
				throw std::runtime_error("Phonem not found in the map of PhonemTranslation by Phonem. " + std::to_string(static_cast<int>(first_phonem)));

			
			// Sort the array so I can simply look up on it later
			std::sort(phonem_translation_list.begin(), phonem_translation_list.end(),
				[&](const auto* a, const auto* b)
				{
					return a->get_nb_phonems() > b->get_nb_phonems();
				});

			(void) state;
			for (auto* phonem_translation: phonem_translation_list) // The pointer can't be NULL
			{
				if (phonem_translation->type == PhonemTranslation::Type::UNIQUE)
				{
					++begin;
					return phonem_translation->get_equivalents()[0].chars; // Todo: make a function to get a random good one
				}
				else // PhonemTranslation::Type::COMPOSITION
				{
					if (static_cast<decltype(end- begin)>(phonem_translation->get_nb_phonems()) > (end - begin))
						continue;
					
					bool is_ok = true;
					// We can start at 1 because the first phonem has already been checked
					for (std::size_t i = 1; i < phonem_translation->get_nb_phonems(); ++i)
					{
						if (*(begin + i) != phonem_translation->translation.composition.phonem[i])
							is_ok = false;
					}

					if (is_ok)
					{
						begin += phonem_translation->get_nb_phonems();
						return phonem_translation->get_equivalents()[0].chars;
					}
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
		StaticMap<Phonem, PhonemTranslation, generated::PHONEM_TO_STRING_SIZE> _map;
};

} // namespace YololTranslator
