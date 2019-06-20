#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <optional>

enum class PositionCondition
{
	BEGIN,
	MIDDLE,
	END
};

inline std::optional<PositionCondition>	position_condition_from_string(std::string_view str)
{
	if (str == "begin")
		return PositionCondition::BEGIN;
	else if (str == "middle")
		return PositionCondition::MIDDLE;
	else if (str == "end")
		return PositionCondition::END;
	else
		return {};
}

struct CharsEquivalent
{
	CharsEquivalent() = default;

	CharsEquivalent(const CharsEquivalent&) = default;
	CharsEquivalent& operator=(const CharsEquivalent&) = default;

	CharsEquivalent(CharsEquivalent&&) = default;
	CharsEquivalent& operator=(CharsEquivalent&&) = default;

	std::string						chars;
	int								weight;
	std::vector<PositionCondition>	position_conditions;
};

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