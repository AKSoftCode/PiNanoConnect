#pragma once

#include "include/IQueryEngine.h"
#include "DevicesList.h"
#include <unordered_map>
#include <future>
#include <atomic>
#include <mutex>

namespace Controller
{
	namespace DataAccess
	{
		using namespace Devices;

		class QueryEngine : public IQueryEngine
		{
			std::mutex gpioCacheMutex_;

			std::mutex analogCacheMutex_;

			std::mutex processStateCacheMutex_;

			std::unordered_map<EDigitalDevices, bool> gpioCache_;

			std::unordered_map<EAnalog, double> analogCache_;

			std::unordered_map<EProcessState, bool> processState_;

			std::future<bool> queryThread_;

			bool QueryThreadFunc() noexcept;

			std::atomic_bool bExitLoop_ = false;


		    double Oxygen = 75; //ppm
		    double Moisture = 75; //ppm

		public:
			QueryEngine();

			~QueryEngine();

			bool getProcessState(EProcessState processType) noexcept override;

		    void setProcessState(EProcessState processType, bool bState) noexcept override;

			bool getDigitalIOValues(EDigitalDevices devices) noexcept override;

			double getAnalogValues(EAnalog analogDevices) noexcept override;
		};
	}
}