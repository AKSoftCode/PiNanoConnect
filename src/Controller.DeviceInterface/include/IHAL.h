#pragma once

#include <cstdint>
#include <cstdint>

#if defined(_MSC_VER)
//  Microsoft 
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
//  GCC
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#else
//  do nothing and hope for the best?
#define EXPORT
#define IMPORT
#pragma warning Unknown dynamic link import/export semantics.
#endif

#if HAL_COMPILING
#   define HAL_LIB_PUBLIC EXPORT
#else
#   define HAL_LIB_PUBLIC IMPORT
#endif

#include "DevicesList.h"

namespace Controller
{
	using namespace Devices;
	namespace HAL 
	{
		//Hardware Abstraction Layer
		class HAL_LIB_PUBLIC IHAL 
		{
		public:
			virtual ~IHAL() {}
			//Digital GPIO
            virtual EGPIOState readDigitalValue(EGPIO bit) noexcept = 0;
			virtual void writeDigitalValue(EGPIO bit, EGPIOState value) noexcept = 0;

			//Analog SPI 
            virtual double readAnalogValue(ESPIDevices device, ESPIChannel channel) noexcept = 0;
			virtual void writeAnalogValue(ESPIDevices device, ESPIChannel channel) noexcept = 0;
		};
	}
}

extern "C"{
	HAL_LIB_PUBLIC Controller::HAL::IHAL& Instance();
}

