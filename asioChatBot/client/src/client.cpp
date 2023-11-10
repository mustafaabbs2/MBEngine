#include <boost/asio.hpp>
#include <iostream>
#include <deque>
#include <iostream>
#include <mutex>


using boost::asio::ip::tcp;

class ChatClient
{
public:
	ChatClient(boost::asio::io_context& io_context, const tcp::resolver::results_type& endpoints)
		: io_context_(io_context)
		, socket_(io_context)
	{
		doConnect(endpoints);
	}

	void write(const std::string& message)
	{
		boost::asio::post(io_context_, [this, message]() {
			bool write_in_progress = !write_msgs_.empty();
			write_msgs_.push_back(message);
			if(!write_in_progress)
			{
				doWrite();
			}
		});
	}

private:
	void doConnect(const tcp::resolver::results_type& endpoints)
	{
		boost::asio::async_connect(
			socket_, endpoints, [this](const boost::system::error_code& ec, const tcp::endpoint&) {
				if(!ec)
				{
					doReadHeader();
				}
			});
	}

	void doReadHeader()
	{
		boost::asio::async_read_until(
			socket_,
			input_buffer_,
			'\n',
			[this](const boost::system::error_code& ec, std::size_t /*bytes_transferred*/) {
				if(!ec)
				{
					std::string message = readBuffer();
					std::cout << message;
					doReadHeader();
				}
				else
				{
					socket_.close();
				}
			});
	}

	void doWrite()
	{
		boost::asio::async_write(
			socket_,
			boost::asio::buffer(write_msgs_.front()),
			[this](const boost::system::error_code& ec, std::size_t /*bytes_transferred*/) {
				if(!ec)
				{
					write_msgs_.pop_front();
					if(!write_msgs_.empty())
					{
						doWrite();
					}
				}
				else
				{
					socket_.close();
				}
			});
	}

	std::string readBuffer()
	{
		std::string data;
		std::istream is(&input_buffer_);
		std::getline(is, data);
		return data;
	}

	boost::asio::io_context& io_context_;
	tcp::socket socket_;
	boost::asio::streambuf input_buffer_;
	std::deque<std::string> write_msgs_;
};

int main(int argc, char* argv[])
{
	try
	{
		if(argc != 3)
		{
			std::cerr << "Usage: chat_client <host> <port>\n";
			return 1;
		}

		boost::asio::io_context io_context;
		tcp::resolver resolver(io_context);
		auto endpoints = resolver.resolve(argv[1], argv[2]);

		ChatClient client(io_context, endpoints);

		// Start a background thread to handle asynchronous operations
		std::thread io_thread([&io_context]() { io_context.run(); });

		// User input loop
		while(true)
		{
			std::string message;
			std::getline(std::cin, message);

			if(message == "/exit")
			{
				break;
			}

			client.write(message + '\n');
		}

		// Close the client
		io_context.stop();
		io_thread.join();
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
