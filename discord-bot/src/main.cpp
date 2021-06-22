#include <iostream>

#include <dpp.h>
#include <thuto/io/file.hpp>
#include <nlohmann/json.hpp>

#include <Translator.hpp>
#include <Command.hpp>

struct Config
{
	std::string word_to_phonems;
	std::string phonems_to_chars;
	std::string word_to_word;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Config, word_to_phonems, phonems_to_chars, word_to_word);
};

Translator create_translator(const std::filesystem::path& config_filename)
{
	using json = nlohmann::json;

	std::ifstream config_stream(config_filename);
	auto config = json::parse(config_stream).get<Config>();

	auto config_dir_path = config_filename.parent_path();
	auto phonems_to_chars = config_dir_path / config.phonems_to_chars;
	auto word_to_phonems = config_dir_path / config.word_to_phonems;
	auto word_to_word = config_dir_path / config.word_to_word;

	return Translator(phonems_to_chars.string(), word_to_phonems.string(), word_to_word.string());
}

void run_client(const Translator& translator)
{
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
	client.run(*token);
}

std::pair<std::string_view, std::filesystem::path> get_arguments(int argc, char** argv)
{
	if (argc < 2)
		throw std::runtime_error("Give me the secret please");

	std::string_view config_filename = (argc > 2) ? argv[2] : "./assets/french_config.json";
	return { argv[1], config_filename };
}

int main(int argc, char** argv)
{
	try
	{
		auto [secret_path, config_filename] = get_arguments(argc, argv);

		const auto token = thuto::read_file(secret_path.data());
		if (!token)
			throw std::runtime_error("Invalid token file.");

		Translator translator = create_translator(config_filename);
		run_client(translator);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception : " << e.what() << std::endl;
		return 1;
	}
}