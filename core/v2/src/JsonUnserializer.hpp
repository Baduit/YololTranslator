#pragma once

#include <external/nlohmann/json.hpp>

#include <PhonemCompositionList.hpp>
#include <CharsEquivalent.hpp>

#include <WordToWord/WordTranslation.hpp>

inline void from_json(const nlohmann::json& j, CharsEquivalent& chars_eq)
{
	//j.at("speed").get_to(s.speed);
	j.at("chars").get_to(chars_eq.chars);
	j.at("weight").get_to(chars_eq.weight);
}

inline void from_json(const nlohmann::json& j, PhonemComposition& phonem_composition)
{
	j.at("phonems").get_to(phonem_composition.phonems);
}

inline void from_json(const nlohmann::json& j, WordTranslation& word_translation)
{
	j.at("weight").get_to(word_translation.weight);
	j.at("chars").get_to(word_translation.chars);
}
