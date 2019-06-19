#pragma once

#include <string>
#include <string_view>
#include <vector>

enum class PositionCondition
{
	BEGIN,
	MIDDLE,
	END
};

struct CharsEquivalent
{
	std::string						chars;
	int								weight;
	std::vector<PositionCondition>	position_conditions;
};

class Phonem
{
	public:
		Phonem() = default;

		Phonem(std::string_view code, std::vector<CharsEquivalent> chars_equivalents):
			_code(code), _chars_equivalents(chars_equivalents)
		{}

		Phonem(const Phonem&) = delete;
		Phonem& operator=(const Phonem&) = delete;

		Phonem(Phonem&&) = default;
		Phonem& operator=(Phonem&&) = default;
	
		std::string_view					get_code() const { return _code; }
		const std::vector<CharsEquivalent>&	get_chars_equivalents() const { return _chars_equivalents; }

		void	get_code(std::string_view code) { _code = code; }
		void	get_chars_equivalents(const std::vector<CharsEquivalent>& chars_equivalents) { _chars_equivalents = chars_equivalents; }

	private:
		std::string						_code;
		std::vector<CharsEquivalent>	_chars_equivalents;
};