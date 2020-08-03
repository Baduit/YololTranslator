#include <iostream>
#include <vector>
#include <string>
#include <string_view>

#include <boost_ut/ut.hpp>

#include <utilities/Split.hpp>

using namespace boost::ut;

void split_simple()
{
	std::vector<std::string_view> expected_result { "Salut", "les", "gens" };

	auto strings = split("Salut les gens", {" "});
	expect(strings.size() == expected_result.size()) << "Check the size";
	expect(strings == expected_result) << "Check the elements";
}

int main()
{
	"case"_test = split_simple;
}