#include <external/nlohmann/json.hpp>
#include <external/magic_enum/magic_enum.hpp>

#include <JsonUnserializer.hpp>

#include <Phonem/PhonemTranslation.hpp>
#include <WordToWord/WordTranslations.hpp>
#include <Phonem/Phonem.hpp>

void from_json(const nlohmann::json& j, WordTranslation& word_translation)
{
	j.at("weight").get_to(word_translation.weight);
	j.at("chars").get_to(word_translation.chars);
}

void from_json(const nlohmann::json& j, Phonem& phonem)
{
	phonem = *magic_enum::enum_cast<Phonem>(j.get<std::string>());
}

void from_json(const nlohmann::json& j, PhonemEquivalent& equivalent)
{
	j.at("chars").get_to(equivalent.chars);
	j.at("weight").get_to(equivalent.weight);

	auto pos_it = j.find("pos");
	if (pos_it != j.end())
	{
		// Default is true everywhere but if it is specified which one are possible that's not the case anymore
		equivalent.can_begin = false;
		equivalent.can_middle = false;
		equivalent.can_end = false;

		if (pos_it->is_array())
		{
			for (const auto& pos: *pos_it)
			{
				auto pos_code = pos.get<std::string>();
				if (pos_code == "begin")
					equivalent.can_begin = true;
				else if (pos_code == "middle")
					equivalent.can_middle = true;
				else if (pos_code == "end")
					equivalent.can_end = true;
			}
		}
		else
		{
			auto pos_code = pos_it->get<std::string>();
			if (pos_code == "begin")
				equivalent.can_begin = true;
			else if (pos_code == "middle")
				equivalent.can_middle = true;
			else if (pos_code == "end")
				equivalent.can_end = true;
		}
	}
}


void from_json(const nlohmann::json& j, PhonemUniqueTranslation& translation)
{
	j.at("code").get_to(translation.phonem);
	j.at("equivalents").get_to(translation._equivalents);
}

void from_json(const nlohmann::json& j, PhonemCompositionTranslation& translation)
{
	j.at("phonems").get_to(translation.phonem);
	j.at("equivalents").get_to(translation._equivalents);
}
