#pragma once

#include <string>
#include "delegate/delegates/delegate.h"
#include "IHAL.h"
#include <any>

using namespace delegates;

#include <memory>

namespace Controller
{
	namespace HAL
	{
		class IDeviceInterface
		{
			using CmdStatusDelegate  = delegate<void, uint8_t, bool> ;
			CmdStatusDelegate cmdDelegate;

		public:
			virtual std::any deviceOperation(std::string jsonParam) noexcept = 0;

			virtual void registerEventCallback(CmdStatusDelegate callback) noexcept = 0;
		};
	}
}

Controller::HAL::IDeviceInterface& getDeviceInterfaceInstance();