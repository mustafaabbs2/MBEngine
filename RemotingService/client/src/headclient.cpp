#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "headprotocol.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
//KVStore
using HeadProtocol::GetReply;
using HeadProtocol::GetRequest;
using HeadProtocol::KVStore;
using HeadProtocol::PutReply;
using HeadProtocol::PutRequest;

//Array transfer
using HeadProtocol::ArrayTransfer;
using HeadProtocol::FloatArray;
using HeadProtocol::IntArray;

class KVStoreClient
{
public:
	KVStoreClient(std::shared_ptr<Channel> channel)
		: stub_(KVStore::NewStub(channel))
	{}

	bool Put(const std::string& key, const std::string& value)
	{
		PutRequest request;
		//setting the two parts of the request struct
		request.set_key(key);
		request.set_value(value);

		PutReply reply;

		ClientContext context;
		Status status = stub_->Put(&context, request, &reply);

		//not using reply anywhere..

		if(!status.ok())
		{
			std::cout << "Error putting key-value pair: " << status.error_message() << std::endl;
			return false;
		}
		return true;
	}

	bool Get(const std::string& key, std::string* value)
	{
		GetRequest request;
		request.set_key(key);

		GetReply reply;
		ClientContext context;
		Status status = stub_->Get(&context, request, &reply);

		if(!status.ok())
		{
			std::cout << "Error getting key-value pair: " << status.error_message() << std::endl;
			return false;
		}
		*value = reply.value();
		return true;
	}

private:
	std::unique_ptr<KVStore::Stub> stub_;
};

class ArrayTransferClient
{
public:
	ArrayTransferClient(std::shared_ptr<Channel> channel)
		: stub_(ArrayTransfer::NewStub(channel))
	{}

	int64_t SendArray(const std::vector<float>& array)
	{
		FloatArray request;
		request.mutable_values()->CopyFrom({array.begin(), array.end()});
		FloatArray response;
		ClientContext context;
		auto start = std::chrono::high_resolution_clock::now();
		Status status = stub_->SendArray(&context, request, &response);
		auto end = std::chrono::high_resolution_clock::now();
		if(status.ok())
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		}
		else
		{
			std::cerr << "RPC failed: " << status.error_code() << ": " << status.error_message()
					  << std::endl;
			return -1;
		}
	}

private:
	std::unique_ptr<ArrayTransfer::Stub> stub_;
};

int main(int argc, char** argv)
{
	// Instantiate the client. It requires a channel, out of which the actual RPCs
	// are created. This channel models a connection to an endpoint (in this case,
	// localhost at port 50051). We indicate that the channel isn't authenticated
	// (use of InsecureChannelCredentials()).
	grpc::ChannelArguments channel_args;
	auto max_receive_message_size = 1024 * 1024 * 50; //default is 4 MB -> set to 50 MB
	channel_args.SetMaxSendMessageSize(max_receive_message_size);
	channel_args.SetMaxReceiveMessageSize(max_receive_message_size);

	std::shared_ptr<Channel> channel = grpc::CreateCustomChannel(
		"localhost:50051", grpc::InsecureChannelCredentials(), channel_args);

	//Client 1

	KVStoreClient KVClient(channel);

	std::string key("mustafa");
	std::string value("99");

	bool reply = KVClient.Put(key, value);

	if(reply)
		std::cout << "KVStore set " << std::endl;
	else
		std::cout << "KVStore not set " << std::endl;

	std::string response;

	// std::string wrongkey("44");
	reply = KVClient.Get(key, &response);

	std::cout << "The value of the key: " << key << " is " << response << std::endl;

	//Client 2

	ArrayTransferClient ArrayClient(channel);

	// std::vector<float> array(256000, 1); //1 MB
	// std::vector<float> array(4000000, 1);//4 million floats ->16 MB
	std::vector<float> array(10000000, 1); //10 million floats -> 40 MB

	int64_t duration = ArrayClient.SendArray(array);
	std::cout << "gRPC: Time taken to send the very large array: " << duration << " milliseconds"
			  << std::endl;

	return 0;
}