#include <boost/asio.hpp>
#include <deque>
#include <iostream>
#include <mutex>

using boost::asio::ip::tcp;

class ChatRoom
{
public:
	void join(std::shared_ptr<tcp::socket> participant)
	{
		participants_.push_back(participant);
		write("Welcome to the chat!\n", participant);
		broadcast("User joined the chat.\n", participant);
	}

	void leave(std::shared_ptr<tcp::socket> participant)
	{
		participants_.erase(std::remove(participants_.begin(), participants_.end(), participant),
							participants_.end());
		broadcast("User left the chat.\n", participant);
	}

	void broadcast(const std::string& message, std::shared_ptr<tcp::socket> sender)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		for(auto& participant : participants_)
		{
			if(participant != sender)
			{
				write(message, participant);
			}
		}
	}

private:
	void write(const std::string& message, std::shared_ptr<tcp::socket> participant)
	{
		boost::asio::async_write(*participant,
								 boost::asio::buffer(message),
								 [this, participant](const boost::system::error_code& ec,
													 std::size_t /*bytes_transferred*/) {
									 if(ec)
									 {
										 leave(participant);
									 }
								 });
	}

	std::vector<std::shared_ptr<tcp::socket>> participants_;
	std::mutex mutex_;
};

//enable a shared pointer to be retrieved from shared_from_this-->
class ChatSession : public std::enable_shared_from_this<ChatSession>
{
public:
	ChatSession(tcp::socket socket, ChatRoom& room)
		: socket_(std::move(socket))
		, room_(room)
	{}

	void start()
	{
		room_.join(std::make_shared<tcp::socket>(std::move(socket_)));
		doRead();
	}

private:
	void doRead()
	{
		auto self(shared_from_this());

		// Initiates an asynchronous read operation on the specified socket -> reads until buffer is full or error code..

		// When the read operation completes (either successfully or due to an error),
		// the provided completion handler is invoked.
		// The handler is responsible for handling the results of the operation. --> the lambda is the handler

		boost::asio::async_read_until(
			socket_,
			buffer_,
			'\n', //reads until newline is encountered
			[this, self](const boost::system::error_code& ec, std::size_t /*bytes_transferred*/) {
				if(!ec)
				{
					room_.broadcast(readBuffer(), self->getSocket());
					doRead();
				}
				else
				{
					room_.leave(self->getSocket());
				}
			});
	}

	std::string readBuffer()
	{
		std::string data;
		std::istream is(&buffer_);
		std::getline(is, data);
		return data;
	}

	std::shared_ptr<tcp::socket> getSocket()
	{
		return std::make_shared<tcp::socket>(std::move(socket_));
	}

	tcp::socket socket_;
	boost::asio::streambuf buffer_;
	ChatRoom& room_;
};

class ChatServer
{
public:
	ChatServer(boost::asio::io_context& io_context, const tcp::endpoint& endpoint)
		: acceptor_(io_context, endpoint)
	{
		doAccept();
	}

private:
	void doAccept()
	{
		acceptor_.async_accept([this](const boost::system::error_code& ec, tcp::socket socket) {
			if(!ec)
			{
				std::make_shared<ChatSession>(std::move(socket), room_)->start();
			}
			doAccept();
		});
	}

	tcp::acceptor acceptor_; //acceptor uses a io_context and a endpoint to listen for requests
	ChatRoom room_;
};

int main()
{
	try
	{
		boost::asio::io_context io_context; //central object for performing async I/O operations

		// Use port 12345, you can change it as needed
		tcp::endpoint endpoint(tcp::v4(), 12345);
		ChatServer server(io_context, endpoint);

		io_context.run();
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}