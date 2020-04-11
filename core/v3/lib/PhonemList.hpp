#pragma once

#include <string_view>
#include <array>

#include <Phonem.hpp>

namespace YololTranslator
{

// Nothing should have more than 50 phonems, later I can put it in a constant that will be set in the generated file to fit perfectly
// later add more template et type erase if startup time is to slow (but it would add a virtual call during the translation)
struct PhonemList
{
	std::array<Phonem, 50> phonems; 
	std::size_t size;
};

} // namespace YololTranslator
