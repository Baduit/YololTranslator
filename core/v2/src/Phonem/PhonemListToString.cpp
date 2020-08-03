#include <algorithm>

#include <Phonem/PhonemListToString.hpp>
#include <JsonUnserializer.hpp>
#include <utilities/File.hpp>

std::string	PhonemListToString::operator()(const std::vector<Phonem>& phonem_list)
{
	std::string result;

	TranslationState state = TranslationState::BEGIN;
	auto it = phonem_list.begin();
	auto end = phonem_list.begin() + static_cast<int>(phonem_list.size());

	while (it != end)
	{
		result += get_possible_equivalent(it, end, state);
		state = get_next_translation_state(state, it, end);
	}

	return result;;
}

void PhonemListToString::load(std::string_view filename)
{
	using json = nlohmann::json;

	json json_content = json::parse(read_at_once(filename));
	{
		json phonems = json_content.at("phonems");
		if (!phonems.is_array())
			throw std::runtime_error("Key phonems should be an array");
		for (const auto& p: phonems)
		{
			_map.emplace_back(p.get<PhonemUniqueTranslation>());
		}
	}
	{
		json phonem_compositions = json_content.at("phonem_compositions");
		if (!phonem_compositions.is_array())
			throw std::runtime_error("Key phonem_compositions should be an array");
		for (const auto& pc: phonem_compositions)
		{
			_map.emplace_back(PhonemTranslation(pc.get<PhonemCompositionTranslation>()));
		}
	}
}

void PhonemListToString::clear()
{
	_map.clear();
}

std::vector<const PhonemTranslation*> PhonemListToString::get_matches(Phonem p) const
{
	std::vector<const PhonemTranslation*> matches;

	for (const auto& translation: _map)
	{
		if (translation.get_first_phonem() == p)
			matches.push_back(&translation);
	}

	return matches;
}