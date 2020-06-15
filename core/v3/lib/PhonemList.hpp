#pragma once

#include <string_view>
#include <array>

#include <Phonem.hpp>

namespace YololTranslator
{

constexpr std::size_t PHONEM_LIST_MAX_SIZE = 50;

// Nothing should have more than 50 phonems, later I can put it in a constant that will be set in the generated file to fit perfectly
// later add more template et type erase if startup time is to slow (but it would add a virtual call during the translation)
struct PhonemList
{
	PhonemList(const PhonemList& other) = default;
	PhonemList& operator=(const PhonemList& other) = default;
	
	PhonemList(PhonemList&& other) = default;
	PhonemList& operator=(PhonemList&& other) = default;

	template <typename ...Args>
	constexpr PhonemList(Args&&... args):
		phonems({args...}),
		size(sizeof...(args))
	{}

	std::array<Phonem, PHONEM_LIST_MAX_SIZE> phonems; 
	std::size_t size;
};

} // namespace YololTranslator
