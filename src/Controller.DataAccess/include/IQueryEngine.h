#pragma once

#include "DevicesList.h"
#include "DataTypes.h"

namespace Controller
{
	using namespace Devices;
	using namespace Settings;

	namespace DataAccess
	{
		class IQueryEngine
		{
		public:

			virtual ~IQueryEngine() {};

			virtual bool getDigitalIOValues(EDigitalDevices devices) noexcept = 0;

			virtual double getAnalogValues(EAnalog analogDevices) noexcept = 0;

			virtual bool getProcessState(EProcessState processType) noexcept = 0;

			virtual void setProcessState(EProcessState processType, bool bState) noexcept = 0;
		};
	}
}

extern "C"
{
	Controller::DataAccess::IQueryEngine& getQueryEngineInstance();
}