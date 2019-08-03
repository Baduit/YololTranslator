#pragma once

#include "CharsEquivalent.hpp"

class Phonem
{
	public:
		Phonem() = default;

		Phonem(std::string_view code, const std::vector<CharsEquivalent>& chars_equivalents):
			_code(code), _chars_equivalents(chars_equivalents)
		{}

		Phonem(std::string&& code, std::vector<CharsEquivalent>&& chars_equivalents):
			_code(std::move(code)), _chars_equivalents(std::move(chars_equivalents))
		{}

		Phonem(const Phonem&) = default;
		Phonem& operator=(const Phonem&) = default;

		Phonem(Phonem&&) = default;
		Phonem& operator=(Phonem&&) = default;
	
		std::string_view					get_code() const { return _code; }
		const std::vector<CharsEquivalent>&	get_chars_equivalents() const { return _chars_equivalents; }

	private:
		std::string						_code;
		std::vector<CharsEquivalent>	_chars_equivalents;
};