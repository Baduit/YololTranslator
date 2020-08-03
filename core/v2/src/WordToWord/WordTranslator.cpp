#include <algorithm>
#include <stdexcept>

#include <WordToWord/WordTranslator.hpp>
#include <JsonUnserializer.hpp>
#include <utilities/File.hpp>

void WordTranslator::load(std::string_view filename)
{
	using json = nlohmann::json;

	json json_content = json::parse(read_at_once(filename));
	json words = json_content.at("words");
	if (!words.is_array())
		throw std::runtime_error("Key words should be an array");
	for (const auto& w: words)
	{
		_map[w.at("word").get<std::string>()].load(w.at("equivalents").get<std::vector<WordTranslation>>());
	}
}

void WordTranslator::clear()
{
	_map.clear();
}

const std::optional<std::string_view>	WordTranslator::operator[](std::string_view word)
{
	auto it = std::find_if(_map.begin(), _map.end(),
		[word](const auto& pair)
		{
			return word == pair.first;
		});
	if (it != _map.end())
		return (it->second)();
	else
		return {};
}