#include "NanoDriver.hpp"

#include <memory>
#if JETSON_NANO_HOST
#include <JetsonGPIO.h>
using namespace GPIO;
#else
#include <wiringPi.h>
#endif

#include "bdc/CircularBuffer.h"
#include "setila_spi.h"
#include "mcp3204.h"
#include <iostream>
#include <spdlog/spdlog.h>
#include "exceptxx/TryCatch.h"

//#include "ABE_ADCDACPi.h"
//
//using namespace ABElectronics_CPP_Libraries;

using namespace Controller;
using namespace HAL;
using namespace Devices;

IHAL& Instance()
{
	static NanoDriver nanoDriverInstance;
	return nanoDriverInstance;
}

NanoDriver::NanoDriver()
{
#if JETSON_NANO_HOST
    GPIO::setmode(GPIO::BOARD);
    GPIO::setwarnings(true);
#else
	wiringPiSetupGpio();
#endif
}

NanoDriver::~NanoDriver()
{
	GPIO::cleanup();
}

EGPIOState NanoDriver::readDigitalValue(EGPIO bit) noexcept
{
   /* try
    {
        std::lock_guard<std::mutex>lg(gpioReadMutex_);
        int value = -1;
    #if JETSON_NANO_HOST
        GPIO::setup(bit, GPIO::IN);
        value = GPIO::input(bit);
    #else
        pinMode(bit, INPUT);
        value = digitalRead(bit);
    #endif
        return (EGPIOState)!value;
    }
    catch(...)
    {
         SPDLOG_ERROR("Error while reading %d bit", bit);
    }
    return EGPIOState::eLOW;*/

	EX_TRY(ex)
	{
		if (mapGPIO_.find(bit) == mapGPIO_.end())
		{
			std::lock_guard<std::mutex>lg(gpioReadMutex_);
			int value = -1;
#if JETSON_NANO_HOST
			GPIO::setup(bit, GPIO::IN);
			value = GPIO::input(bit);
#else
			pinMode(bit, INPUT);
			value = digitalRead(bit);
#endif
			mapGPIO_.emplace(bit, value ? EGPIOState::eLOW : EGPIOState::eHIGH);
		}
	}
	EX_CATCH(ex);

	if (ex)
	{
		SPDLOG_ERROR("Exception : {} ", ex->what());
	}
	return mapGPIO_.at(bit);
}

void NanoDriver::writeDigitalValue(EGPIO bit, EGPIOState value) noexcept
{
	EX_TRY(ex)
    {
        if(readDigitalValue(bit) != value)
        {
            std::lock_guard<std::mutex>lg(gpioReadMutex_);
    #if JETSON_NANO_HOST
            GPIO::setup(bit, GPIO::OUT);
            GPIO::output(bit, value == 1 ? 0 : 1);
    #else
            pinMode(bit, OUTPUT);
            digitalWrite(bit, value == 1 ? LOW : HIGH);
    #endif
			mapGPIO_[bit] = value;
        }
	}
	EX_CATCH(ex);

	if (ex)
	{
		SPDLOG_ERROR("Exception : {} ", ex->what());
		SPDLOG_ERROR("Error while writing %d bit with %d value", bit, value);
	}
}

double NanoDriver::readAnalogValue(ESPIDevices device, ESPIChannel channel) noexcept
{
	EX_TRY(ex)
	{
		std::lock_guard<std::mutex>lg(gpioReadMutex_);
		int rc;

		std::string spiDevice = "";
		switch (device)
		{
		case ESPIDevices::eSPI1:
			spiDevice = "/dev/spidev0.0";
			break;
		case ESPIDevices::eSPI2:
			spiDevice = "/dev/spidev1.1";
			break;
		default:
			break;
		}

		MCP3204_INPUT_CHANNEL deviceChannel;
		switch (channel)
		{
		case ESPIChannel::eCH0:
			deviceChannel = MCP3204_INPUT_CHANNEL::CH0;
			break;
		case ESPIChannel::eCH1:
			deviceChannel = MCP3204_INPUT_CHANNEL::CH1;
			break;
		case ESPIChannel::eCH2:
			deviceChannel = MCP3204_INPUT_CHANNEL::CH2;
			break;
		case ESPIChannel::eCH3:
			deviceChannel = MCP3204_INPUT_CHANNEL::CH3;
			break;
		default:
			break;
		}

		std::unique_ptr<SPI_Bus_Master_Device> spi_bus_master = std::make_unique<SPI_Bus_Master_Device>(spiDevice);

		std::unique_ptr<MCP3204> ad_MCP3204 = std::make_unique<MCP3204>(4.096);

		if (spi_bus_master->open_bus())
		{
			std::cout << "Failed to open bus master device." << std::endl;
			return -1;
		}

		if (spi_bus_master->configure(SPI_BUS_MODE::MODE_0, MCP3204_SPI_BUS_SPEED, MCP3204_SPI_BITS_PER_WORD, 0))
		{
			std::cout << "Setting SPI bus master parameters failed." << std::endl;
			return -1;
		}

		if (ad_MCP3204->attach_to_bus(spi_bus_master.get()))
		{
			std::cout << "Attach to SPI bus master failed." << std::endl;
			return -1;
		}


		rc = ad_MCP3204->convert(deviceChannel, MCP3204_INPUT_CHANNEL_MODE::SINGLE_ENDED);

		if (rc)
		{
			std::cout << "MCP3204 Error: communication error while asking for AD conversion. Error code: " << rc << std::endl;
			return -1;
		}

		std::cout << "Digital value of the sensor reading: " << ad_MCP3204->digital_value() << std::endl;
		std::cout << "Analog value: " << ad_MCP3204->analog_value() << "V" << std::endl;


		auto analogValCount = ad_MCP3204->digital_value();

		ad_MCP3204->dettach_from_master_bus();

		ad_MCP3204.reset(nullptr);

		spi_bus_master->close_bus();

		spi_bus_master.reset(nullptr);

		return analogValCount;
	}
	EX_CATCH(ex);

	if (ex)
	{
		SPDLOG_ERROR("Exception : {} ", ex->what());
	}

	return 0;
}

void NanoDriver::writeAnalogValue(ESPIDevices device, ESPIChannel channel) noexcept
{
   // std::lock_guard<std::mutex>lg(gpioReadMutex_);
   // ADCDACPi adcdac;

   // if (adcdac.open_dac() != 1){ // open the DAC spi channel
   //     return; // if the SPI bus fails to open exit the program
   // }

   // adcdac.set_dac_gain(2); // set the dac gain to 2 which will give a voltage range of 0 to 3.3V

   // adcdac.set_dac_voltage(1.2, 1); // set the voltage on channel 1 to 1.2V
   //// adcdac.set_dac_voltage(3.1, 2); // set the voltage on channel 2 to 3.1V

   // adcdac.close_dac();

   // printf("dac values written\n");
}
