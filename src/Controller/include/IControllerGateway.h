#pragma once

#include <string>
namespace Controller
{
	namespace Gateway
	{
		class IControllerGateway
		{
		public:
			//virtual ~IGrpcCommsAPI() = 0;


            virtual void StartServer(std::string serverAddress) = 0;

			virtual void StopServer() noexcept = 0;
		};
	}
}

Controller::Gateway::IControllerGateway& getCommsInstance();
