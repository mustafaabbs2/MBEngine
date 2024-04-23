#include "headprotocol.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <unordered_map>

using namespace HeadProtocol;
using namespace std;

//Class 1: Key Value Pair
class KVStoreImpl final : public KVStore::Service
{
public:
	grpc::Status
	Put(grpc::ServerContext* context, const PutRequest* request, PutReply* reply) override
	{
		store_[request->key()] = request->value();
		// A cout will not be displayed
		// std::cout<<"Setting kvp on the server"<<std::endl;
		reply->set_success(true);
		return grpc::Status::OK;
	}

	grpc::Status
	Get(grpc::ServerContext* context, const GetRequest* request, GetReply* reply) override
	{
		auto it = store_.find(request->key());
		if(it == store_.end())
		{
			return grpc::Status(grpc::NOT_FOUND, "Key not found");
		}
		reply->set_value(it->second);
		return grpc::Status::OK;
	}

private:
	unordered_map<string, string> store_;
};

//Class 2: Transfer large arrays
class ArrayTransferServiceImpl final : public ArrayTransfer::Service
{
public:
	grpc::Status SendArray(grpc::ServerContext* context,
						   const FloatArray* request,
						   FloatArray* response) override
	{
		*response = *request;
		return grpc::Status::OK;
	}
};

int main()
{

	KVStoreImpl KVPService_;
	ArrayTransferServiceImpl ArrayService_;

	grpc::ServerBuilder builder;

	builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());

	//Maybe you need to do this in the server
	builder.SetMaxSendMessageSize(1024 * 1024 * 50);
	builder.SetMaxMessageSize(1024 * 1024 * 50);
	builder.SetMaxReceiveMessageSize(1024 * 1024 * 50);

	builder.RegisterService(&KVPService_);
	builder.RegisterService(&ArrayService_);

	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

	cout << "Server listening on 0.0.0.0:50051" << endl;
	server->Wait();
}
