#pragma once

#include <IHAL.h>
#include <map>
#include <array>
#include <map>
using namespace Controller::HAL;

namespace Controller
{
	namespace HAL {
		class NanoSimDriver : public IHAL
		{
		public:
			explicit NanoSimDriver();

			~NanoSimDriver() = default; 
			//Digital GPIO
            virtual EGPIOState readDigitalValue(EGPIO bit) noexcept override;
			virtual void writeDigitalValue(EGPIO bit, EGPIOState value) noexcept override;

			//Analog SPI 
            virtual double readAnalogValue(ESPIDevices device, ESPIChannel channel) noexcept override;
			virtual void writeAnalogValue(ESPIDevices device, ESPIChannel channel) noexcept override;
		private:
			void Initialize();

			std::map<EGPIO, EGPIOState> mapGPIO_;

			std::map<ESPIDevices, std::array<double, 4>> mapAnalogOp_;
		};
	}
}
