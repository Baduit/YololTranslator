#pragma once

#include <memory>
#include <map>
#include <iostream>

#include <uwebsockets/App.h>
#include <nameof.hpp>

#include <WSAdapter.hpp>
#include <Translator.hpp>

class WSService
{
	public:
		WSService(Translator& translator, int port);

		void run();

	private:
		void handle_open(WSAdapter ws);
		void handle_message(WSAdapter ws, std::string_view message);
		void handle_close(WSAdapter ws);

		void publish(std::string_view topic, std::string_view message);
		void publish_message(std::string_view topic, const messages::Message& message);

		void handle_config(WSAdapter ws, SocketData& socket_data, nlohmann::json&& message);
		void handle_translate(WSAdapter ws, SocketData& socket_data, nlohmann::json&& message);

	private:
		using CommandHandler = void (WSService::*)(WSAdapter ws, SocketData& socket_data, nlohmann::json&& message);

		Translator& _translator;
		uWS::App _app;
		std::map<std::string_view, CommandHandler> _handlers;
};
