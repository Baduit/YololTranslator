#include "PhonemList.hpp"

PhonemList::PhonemList(std::string_view filename)
{
	load_from_file(filename);
}

void	PhonemList::load_from_file(std::string_view filename)
{
	// do stuff
}

const std::vector<Phonem>&	PhonemList::get_phonems() const
{
	return _phonems;
}