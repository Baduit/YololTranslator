#pragma once

#include <nlohmann/json.hpp>
#include <uwebsockets/App.h>

#include <SocketData.hpp>
#include <Messages.hpp>

class WSAdapter
{
	#ifdef _WIN32
		using WebsocketImpl = uWS::WebSocket<false, true>;
	#else
		using WebsocketImpl = uWS::WebSocket<false, true, SocketData>;
	#endif

	public:
		WSAdapter(WebsocketImpl* ws):
			_ws(ws)
		{}

		WSAdapter(const WSAdapter&) = default;
		WSAdapter& operator=(const WSAdapter&) = default;

		WSAdapter(WSAdapter&&) = default;
		WSAdapter& operator=(WSAdapter&&) = default;

		bool send_error(std::string_view message)
		{
			return send(generate_error(message));
		}

		bool send_message(const messages::Message& message)
		{
			return send(messages::to_string(message));
		}

		void subscribe(std::string_view topic)
		{
			_ws->subscribe(topic);
		}

		SocketData& get_socket_data()
		{
			// Can't be null
			return *reinterpret_cast<SocketData*>(_ws->getUserData());
		}

		void publish_message(std::string_view topic, const messages::Message& message)
		{
			publish(topic, messages::to_string(message));
		}

	private:
		bool send(std::string_view message)
		{
			return _ws->send(message, uWS::OpCode::TEXT);
		}

		void publish(std::string_view topic, std::string_view message)
		{
			_ws->publish(topic, message, uWS::OpCode::TEXT);
		}

		std::string generate_error(std::string_view message)
		{
			nlohmann::json error;
			error["message_type"] = "Error";
			error["message"] = message;
			return error.dump();
		}

	private:
		WebsocketImpl* _ws;
};
