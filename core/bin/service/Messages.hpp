#pragma once

#include <variant>
#include <string>
#include <string_view>
#include <utility>

#include <nlohmann/json.hpp>

#include <nameof_utils.hpp>

namespace messages
{

struct ConfigAck
{
	bool success;
	int request_id;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ConfigAck, success, request_id)

struct Translation
{
	std::string text;
	int request_id;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Translation, text, request_id)

using Message = std::variant<ConfigAck, Translation>;
/* void to_json(nlohmann::json& j, const Message& message)
{
	std::visit(
		[&](const auto& m)
		{
			to_json(j, m);
		}, message);
} */

inline std::string to_string(const Message& message)
{
	nlohmann::json str;
	std::visit(
		[&](const auto& m)
		{
			str["message_type"] = get_name_of_class<decltype(m)>();
			str["data"] = m;
		}, message);
	return str.dump();
}

} // namespace messages