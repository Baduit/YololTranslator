#pragma once

#include <vector>
#include <string>

#include "CharsEquivalent.hpp"

using PhonemCode = std::string;

class PhonemComposition
{
	public:
		PhonemComposition() = default;

		PhonemComposition(const std::vector<PhonemCode>& phonems, const std::vector<CharsEquivalent>& eq):
			_phonems(phonems), _chars_equivalents(eq)
		{}

		PhonemComposition(std::vector<PhonemCode>&& phonems, std::vector<CharsEquivalent>&& eq):
			_phonems(std::move(phonems)), _chars_equivalents(std::move(eq))
		{}

		PhonemComposition(const PhonemComposition&) = default;
		PhonemComposition& operator=(const PhonemComposition&) = default;

		PhonemComposition(PhonemComposition&&) = default;
		PhonemComposition& operator=(PhonemComposition&&) = default;

		bool operator<(const PhonemComposition& other) const
		{
			if (_phonems.size() < other._phonems.size())
				return true;
			else
				return _chars_equivalents < other._chars_equivalents;
		}
	
		const std::vector<PhonemCode>&		get_phonems() const { return _phonems; }
		const std::vector<CharsEquivalent>&	get_chars_equivalents() const { return _chars_equivalents; }

	private:
		std::vector<PhonemCode>			_phonems;
		std::vector<CharsEquivalent>	_chars_equivalents;
};