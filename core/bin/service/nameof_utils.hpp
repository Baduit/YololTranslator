#pragma once

#include <string_view>

#include <nameof.hpp>

template <typename T>
std::string_view get_name_of_class()
{
	std::string_view name = nameof::nameof_type<T>();
	auto pos = name.find_last_of(':');
	if (pos != std::string_view::npos)
		return name.substr(pos + 1);
	else
		return name;
}