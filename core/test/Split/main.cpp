#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <iostream>
#include <vector>
#include <string>
#include <string_view>

#include <utilities/Split.hpp>

TEST_CASE("basic")
{
	std::vector<std::string_view> expected_result { "Salut", "les", "gens" };

	auto strings = split("Salut les gens", {" "});
	REQUIRE_MESSAGE(strings.size() == expected_result.size(), "Check the size");
	CHECK_MESSAGE(strings == expected_result, "Check the elements");
}