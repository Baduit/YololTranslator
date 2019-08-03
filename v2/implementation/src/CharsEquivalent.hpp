#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <iostream>

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

	bool operator<(const CharsEquivalent& other) const
	{
		return chars < other.chars;
	}

	std::string						chars;
	int								weight;
	std::vector<PositionCondition>	position_conditions;
};