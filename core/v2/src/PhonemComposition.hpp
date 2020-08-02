#pragma once

#include <vector>
#include <string>

#include <CharsEquivalent.hpp>

using PhonemCode = std::string;

struct PhonemComposition
{
	PhonemComposition() = default;

	PhonemComposition(const std::vector<PhonemCode>& p, const std::vector<CharsEquivalent>& eq):
		phonems(p), chars_equivalents(eq)
	{}

	PhonemComposition(std::vector<PhonemCode>&& p, std::vector<CharsEquivalent>&& eq):
		phonems(std::move(p)), chars_equivalents(std::move(eq))
	{}

	PhonemComposition(const PhonemComposition&) = default;
	PhonemComposition& operator=(const PhonemComposition&) = default;

	PhonemComposition(PhonemComposition&&) = default;
	PhonemComposition& operator=(PhonemComposition&&) = default;

	bool operator<(const PhonemComposition& other) const
	{
		if (phonems.size() < other.phonems.size())
			return true;
		else
			return chars_equivalents < other.chars_equivalents;
	}

	std::vector<PhonemCode>			phonems;
	std::vector<CharsEquivalent>	chars_equivalents;
};