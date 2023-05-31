#include "NanoSimDriver.hpp"
#include <memory>
#include "exceptxx/TryCatch.h"
#include <spdlog/spdlog.h>

using namespace Controller;
using namespace HAL;
using namespace Devices;

Controller::HAL::IHAL& Instance()
{
	static NanoSimDriver nanoSimDriverInstance;
	return nanoSimDriverInstance;
}

NanoSimDriver::NanoSimDriver()
{
	Initialize();
}

void NanoSimDriver::Initialize()
{
	EX_TRY(ex)
	{
		// Initialze GPIO
		mapGPIO_.emplace(EGPIO::eGPIO7, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO11, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO12, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO13, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO15, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO16, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO18, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO19, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO21, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO22, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO23, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO24, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO26, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO29, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO31, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO32, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO33, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO35, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO36, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO37, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO38, EGPIOState::eLOW);
		mapGPIO_.emplace(EGPIO::eGPIO40, EGPIOState::eLOW);

		//Initialize ADC values
		mapAnalogOp_.emplace(std::make_pair<ESPIDevices, std::array<double, 4>>(ESPIDevices::eSPI1, { 0 }));

		//Initalize DAC values
		mapAnalogOp_.emplace(std::make_pair<ESPIDevices, std::array<double, 4>>(ESPIDevices::eSPI1, { 0 }));
	}
	EX_CATCH(ex);

	if (ex)
	{
		SPDLOG_ERROR("Exception : {} ", ex->what());
	}
}


EGPIOState NanoSimDriver::readDigitalValue(EGPIO bit)  noexcept
{
	return mapGPIO_.at(bit);
}

void NanoSimDriver::writeDigitalValue(EGPIO bit, EGPIOState value) noexcept
{
	mapGPIO_[bit] = value;
}

double NanoSimDriver::readAnalogValue(ESPIDevices device, ESPIChannel channel)  noexcept
{
	return 0.0;
}

void NanoSimDriver::writeAnalogValue(ESPIDevices device, ESPIChannel channel) noexcept
{
}
