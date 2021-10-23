#include <stdexcept>

#include <utilities/Random.hpp>
#include <WordToWord/WordTranslations.hpp>

void WordTranslationContainer::load(std::vector<WordTranslation> new_translations)
{
	if (_translation.empty())
		_translation = std::move(new_translations);
	else
		_translation.insert(std::end(_translation),
					std::make_move_iterator(std::begin(new_translations)),
					std::make_move_iterator(std::end(new_translations)));	
}

void WordTranslationContainer::clear()
{
	_translation.clear();
}

std::string_view WordTranslationContainer::operator()() const
{
	return get_random_translation();
}

std::string_view WordTranslationContainer::get_random_translation() const
{
	return get_translation(Random::rand(get_max_random_range()));
}

std::size_t WordTranslationContainer::get_max_random_range() const
{
	std::size_t result = 0;
	for (const auto& t: _translation)
	{
		result += t.weight;
	}
	return result;
}

std::string_view WordTranslationContainer::get_translation(std::size_t weighted_index) const
{
	std::size_t i = 0;
	for (const auto& t: _translation)
	{
		i += t.weight;
		if (i >= weighted_index)
			return t.chars;
	}
	throw std::runtime_error("WordTranslationContainer failed while choosing a translation.");
}