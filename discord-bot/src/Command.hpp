#pragma once

#include <string_view>
#include <optional>

// Be carefull to not use a command when the string_views are not valid anymore
struct Command
{
	Command(std::string_view command_name):
		name(command_name),
		message("")
	{}

	Command(std::string_view command_name, std::string_view command_message):
		name(command_name),
		message(command_message)
	{}

	// To finish, this is not valid at all for now
	static constexpr std::optional<Command> parse(std::string_view message_content)
	{
		if (message_content.size() < 2 || !message_content.starts_with('!'))
			return {};

		auto first_space_index = message_content.find(' ');
		if (first_space_index == std::string_view::npos)
		{
			return Command(message_content.substr(1));
		}
		else
		{
			auto name_end_index = first_space_index - 1;
			auto message_begin_index = message_content.find_first_not_of(' ', first_space_index);
			if (message_begin_index == std::string_view::npos)
				return Command(message_content.substr(1, name_end_index));
			else
				return Command(message_content.substr(1, name_end_index), message_content.substr(message_begin_index));
		}
	}

	std::string_view name;
	std::string_view message;
};