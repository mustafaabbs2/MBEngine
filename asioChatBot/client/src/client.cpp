#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <iostream>
#include <string>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http; // from <boost/beast/http.hpp>
namespace net = boost::asio; // from <boost/asio.hpp>
using tcp = net::ip::tcp; // from <boost/asio/ip/tcp.hpp>

int main()
{
	try
	{
		// Create the I/O context and an endpoint for the server to listen on
		net::io_context ioc;
		tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));

		while(true)
		{
			// Create a socket and accept a connection from a client
			tcp::socket socket(ioc);
			acceptor.accept(socket);

			// Read the HTTP request
			beast::flat_buffer buffer;
			http::request<http::string_body> request;
			http::read(socket, buffer, request);

			// Create the HTTP response
			http::response<http::string_body> response;
			response.version(request.version());
			response.keep_alive(false);
			response.result(http::status::ok);
			response.set(http::field::content_type, "application/json");

			// Construct the response body
			std::string message = R"({"message": "Hello, World!"})";
			response.body() = message;
			response.prepare_payload();

			// Send the HTTP response
			http::write(socket, response);

			// Gracefully close the socket
			beast::error_code ec;
			socket.shutdown(tcp::socket::shutdown_send, ec);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}