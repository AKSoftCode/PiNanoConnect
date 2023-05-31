#include "include/IControllerGateway.h"

namespace Controller
{
	namespace Gateway
	{
		class ControllerGateway : public IControllerGateway
		{
		public:

		    virtual ~ControllerGateway() = default;

            virtual void StartServer(std::string serverAddress) override;

			virtual void StopServer() noexcept override;
		};
	}
}
