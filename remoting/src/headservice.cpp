#include <iostream>
#include <unordered_map>
#include <grpcpp/grpcpp.h>
#include "kvp.grpc.pb.h"

using namespace kvstore;
using namespace std;

class KVStoreImpl final : public KVStore::Service {
public:
    grpc::Status Put(grpc::ServerContext* context, const PutRequest* request, PutReply* reply) override {
        store_[request->key()] = request->value();
        // A cout will not be displayed
        // std::cout<<"Setting kvp on the server"<<std::endl;
        reply->set_success(true);
        return grpc::Status::OK;
    }

    grpc::Status Get(grpc::ServerContext* context, const GetRequest* request, GetReply* reply) override {
        auto it = store_.find(request->key());
        if (it == store_.end()) {
            return grpc::Status(grpc::NOT_FOUND, "Key not found");
        }
        reply->set_value(it->second);
        return grpc::Status::OK;
    }

private:
    unordered_map<string, string> store_;
};

int main() {
    grpc::ServerBuilder builder;
    KVStoreImpl service_;
    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
    builder.RegisterService(&service_);
    unique_ptr<grpc::Server> server(builder.BuildAndStart());
    cout << "Server listening on 0.0.0.0:50051" << endl;
    server->Wait();
}
