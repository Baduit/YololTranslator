#include <PhonemCompositionList.hpp>

#include <fstream>
#include <stdexcept>

#include <external/nlohmann/json.hpp>
#include <JsonUnserializer.hpp>

PhonemCompositionList::PhonemCompositionList(std::string_view filename)
{
	load_from_file(filename);
}

void	PhonemCompositionList::load_from_file(std::string_view filename)
{
	using namespace std::string_literals;

	_phonem_compositions.clear();

	std::ifstream dict_file(filename.data());
	if (!dict_file)
		throw std::runtime_error("Error while opening file: "s + filename.data());

	// this could be optimized, but it will not be called often
	std::string file_content;
	std::string line;
	while (std::getline(dict_file, line))
	{
		file_content += line;
	}

	json json_content = json::parse(file_content);
	for (const auto& pc: json_content.at("phonem_compositions"))
	{
		std::vector<PhonemCode>  phonem_codes = pc.at("phonems").get<std::vector<PhonemCode>>();

		std::vector<CharsEquivalent> chars_eq;
		for (const auto& cs: pc.at("equivalents"))
		{
			CharsEquivalent eq;

			eq.chars = cs.at("chars").get<std::string>();
			eq.weight = cs.at("weight").get<int>();
			eq.composition_size = phonem_codes.size();
			
			chars_eq.push_back(std::move(eq));
		}

		_phonem_compositions.emplace_back(std::move(phonem_codes), std::move(chars_eq));
	}
	std::sort(_phonem_compositions.begin(), _phonem_compositions.end());
}

const std::vector<PhonemComposition>&	PhonemCompositionList::get_phonem_compositions() const
{
	return _phonem_compositions;
}
