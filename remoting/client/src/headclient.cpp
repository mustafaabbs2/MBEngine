#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "kvp.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using kvstore::PutRequest;
using kvstore::GetRequest;
using kvstore::GetReply;
using kvstore::PutReply;
using kvstore::KVStore;

class KVStoreClient {
 public:
  KVStoreClient(std::shared_ptr<Channel> channel)
      : stub_(KVStore::NewStub(channel)) {}

  bool Put(const std::string& key, const std::string& value) {
    PutRequest request;
    //setting the two parts of the request struct
    request.set_key(key);
    request.set_value(value);

    PutReply reply;

    ClientContext context;
    Status status = stub_->Put(&context, request, &reply);

    //not using reply anywhere..

    if (!status.ok()) {
      std::cout << "Error putting key-value pair: " << status.error_message()
                << std::endl;
      return false;
    }
    return true;
  }

  bool Get(const std::string& key, std::string* value) {
    GetRequest request;
    request.set_key(key);

    GetReply reply;
    ClientContext context;
    Status status = stub_->Get(&context, request, &reply);

    if (!status.ok()) {
      std::cout << "Error getting key-value pair: " << status.error_message()
                << std::endl;
      return false;
    }
    *value = reply.value();
    return true;
  }

 private:
  std::unique_ptr<KVStore::Stub> stub_;
};


int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  KVStoreClient kvclient(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));

  std::string key("mustafa");
  std::string value("99");

  bool reply = kvclient.Put(key, value);
  
  if (reply)
    std::cout << "KVStore set " << std::endl;
  else
    std::cout << "KVStore not set " << std::endl;

  std::string response;

  std::string wrongkey("44");
  reply = kvclient.Get(wrongkey, &response);
  
  // std::cout << "The value of the key: "<< key <<" is " << response << std::endl;

  return 0;
}