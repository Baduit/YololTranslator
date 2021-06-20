#include <iostream>
#include <dpp.h>

int main()
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
			if (message.content == "jaaj?")
			{
				message.channel().send("jooj"); // or message.reply("jooj"), which mentions the message author
			}
		};

	client.run(token);
}