#include <dpp.h>

#include <iostream>

#include <Command.hpp>

int main(int argc, char** argv)
{
	const std::string token = "BOT_TOKEN_HERE";
	dpp::Client client;

	client.onReady =
		[&]()
		{
			std::cout << "hello, c++!\n";
			std::cout << client.user.id << "\n\n";
		};

	client.onMessage =
		[&](const dpp::Message &message)
		{
			if (message.content == "jaaj")
			{
				message.channel().send("jooj");
			}
			else if (message.content == "!vdd")
			{
				message.reply("translation of vdd message");
			}
		};

	client.run(token);
}