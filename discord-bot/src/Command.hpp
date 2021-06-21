#pragma once

#include <string_view>
#include <optional>

// Be carefull to not use a command when the string_views are not valid anymore
struct Command
{
	// To finish, this is not valid at all for now
	static constexpr std::optional<Command> parse(std::string_view message_content)
	{
		if (message_content.size() < 2 || !message_content.starts_with('!'))
			return {};

		auto first_space_index = message_content.find(' ');
		if (first_space_index = std::string_view::npos)
		{
			return Command{ .name = message_content, .message = "" };
		}
		else
		{
			return Command{ .name = message_content, .message = "" };
		}
	}

	std::string_view name;
	std::string_view message;
};