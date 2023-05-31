#pragma once
#include "IHAL.h"
#include <mutex>
#include <map>
namespace Controller 
{
	namespace HAL 
	{
		class NanoDriver : public IHAL
		{
		public:

			NanoDriver();
			~NanoDriver();
			//Digital GPIO
            virtual EGPIOState readDigitalValue(EGPIO bit) noexcept override;
			virtual void writeDigitalValue(EGPIO bit, EGPIOState value) noexcept override;

			//Analog SPI 
            virtual double readAnalogValue(ESPIDevices device, ESPIChannel channel) noexcept override;
			virtual void writeAnalogValue(ESPIDevices device, ESPIChannel channel) noexcept override;

		private:
			std::mutex gpioReadMutex_;
			std::map<EGPIO, EGPIOState> mapGPIO_;
		};
	}
}
