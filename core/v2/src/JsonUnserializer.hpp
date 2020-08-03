#pragma once

#include <external/nlohmann/json.hpp>

#include <Phonem/Phonem.hpp>

class WordTranslation;
class PhonemEquivalent;
class PhonemUniqueTranslation;
class PhonemCompositionTranslation;

void from_json(const nlohmann::json& j, WordTranslation& word_translation);
void from_json(const nlohmann::json& j, Phonem& phonem);
void from_json(const nlohmann::json& j, PhonemEquivalent& equivalent);
void from_json(const nlohmann::json& j, PhonemUniqueTranslation& translation);
void from_json(const nlohmann::json& j, PhonemCompositionTranslation& translation);
