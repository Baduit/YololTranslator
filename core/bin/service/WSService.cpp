#include <WSService.hpp>

WSService::WSService(Translator& translator, int port):
	_translator(translator)
{
	_handlers["config"] = &WSService::handle_config;
	_handlers["translate"] = &WSService::handle_translate;

	_app.ws<SocketData>("/*", {
			.open =
				[this](auto* ws)
				{
					handle_open(WSAdapter(ws));
				},
			.message =
				[this](auto* ws, std::string_view message, uWS::OpCode)
				{
					handle_message(WSAdapter(ws), message);
				},
			.drain =
				[](auto* ws)
				{
					std::cout << "Buffered amount == " << ws->getBufferedAmount() << std::endl;
				},
			.close =
				[this](auto* ws, int /* code */, std::string_view /*message*/)
				{
					handle_close(WSAdapter(ws));
				}
		})
		.listen(port,
			[port](auto* listenSocket)
			{
				if (listenSocket)
					std::cout << "Listening on port " << port << "\n";
			})
		.run();
}

void WSService::run()
{
	_app.run();
}

void WSService::handle_open(WSAdapter)
{
	
}

void WSService::handle_message(WSAdapter ws, std::string_view message)
{
	try
	{
		SocketData& socket_data = ws.get_socket_data();

		nlohmann::json parsed_message = nlohmann::json::parse(message);
		std::string_view message_type = parsed_message.at("type").get<std::string_view>();
		auto it = _handlers.find(message_type);
		if (it == _handlers.end())
			throw std::runtime_error("Unknown message type " + std::string(message_type) + "!");
		auto method = it->second;
		(this->*method)(ws, socket_data, std::move(parsed_message));
	}
	catch(const std::exception& e)
	{
		std::cout << "Exception : " << e.what() << std::endl;
		ws.send_error(e.what());
	}
					
}

void WSService::handle_close(WSAdapter ws)
{
}

void WSService::handle_config(WSAdapter ws, SocketData& socket_data, nlohmann::json&& message)
{

}

void WSService::handle_translate(WSAdapter ws, SocketData& socket_data, nlohmann::json&& message)
{

}

void WSService::publish(std::string_view topic, std::string_view message)
{
	_app.publish(topic, message, uWS::OpCode::TEXT);
}

void WSService::publish_message(std::string_view topic, const messages::Message& message)
{
	publish(topic, messages::to_string(message));
}
