#include "ControllerGateway.hpp"

#include "Proto/Controller.grpc.pb.h"

#include <fstream>
#include <sstream>

#include "ControllerCommsAPIService.hpp"

#include <spdlog/spdlog.h>

using namespace Controller;
using namespace Gateway;

IControllerGateway& getCommsInstance()
{
    static ControllerGateway commsApi;
    return commsApi;
}

void ControllerGateway::StartServer(std::string serverAddress)
{
    ControllerCommsAPIServiceImpl service;

    ServerBuilder builder;

    auto readAllFile = [](const char* filename)
    {
        std::string data;
        std::ifstream file(filename, std::ios::in);

        if (file.is_open())
        {
            std::stringstream ss;
            ss << file.rdbuf();

            file.close();

            data = ss.str();
        }

        return data;
    };

    std::string key;
    std::string cert;
    std::string root;

    cert = readAllFile("https-web.pem");
    key = readAllFile("https-web.key");
    root = readAllFile("rootCA.pem");


    grpc::SslServerCredentialsOptions ssl_opts;
    ssl_opts.pem_key_cert_pairs.push_back({ key, cert });
    ssl_opts.pem_root_certs = root;
    ssl_opts.client_certificate_request = GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE;

    builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());

    builder.RegisterService(&service);


    std::unique_ptr<Server> server(builder.BuildAndStart());

    SPDLOG_INFO("Server listening on port: {}", serverAddress);
    std::cout << "Server listening on port: " << serverAddress << std::endl;

    server->Wait();
    server->Shutdown();
}

void ControllerGateway::StopServer() noexcept
{
}
