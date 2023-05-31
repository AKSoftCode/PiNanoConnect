#pragma once
#include <map>
#include <math.h>  

namespace Controller
{
	namespace Devices
	{
		enum class EDigitalDevices
		{
			eParam1,
			eParam2,
			eParam3,
			eParam4,

			eParam5,
			eParam6,

			eParam7,
			eParam8,

			eParam9,
			eParam10,
			eParam11,

			eParam12,
		};

		enum class EAnalog
		{
			eParam1,
			eParam2,
			eParam3,
			eParam4,
			eParam5
		};

		enum class EProcessState
		{
			eProcess1,
			eProcess2,
			eProcess3,
			eProcess4,
			eProcess5,
			eProcess6
		};

		enum EGPIOState : unsigned short
		{
			eLOW = 0,
			eHIGH,			
		};


		enum class ESPIDevices {
			eSPI1,
			eSPI2
		};

		enum class ESPIChannel {
			eCH0,
			eCH1,
			eCH2,
			eCH3,

		};


		enum EGPIO : unsigned short
        {
			eGPIO7 = 7,
			eGPIO11 = 11,
			eGPIO12 = 12,
			eGPIO13 = 13,
			eGPIO15 = 15,
            eGPIO16 = 16, //LDAC 26
			eGPIO18 = 18,
			eGPIO19 = 19,
			eGPIO21 = 21,
			eGPIO22 = 22,
			eGPIO23 = 23,
			eGPIO24 = 24,
			eGPIO26 = 26,
			eGPIO29 = 29,
			eGPIO31 = 31,
			eGPIO32 = 32,
			eGPIO33 = 33,
			eGPIO35 = 35,
			eGPIO36 = 36,
			eGPIO37 = 37,
			eGPIO38 = 38,
			eGPIO40 = 40
		};


		static std::map<Controller::Devices::EDigitalDevices, EGPIO> GPIODevicesMap = {

            {EDigitalDevices::eParam1, EGPIO::eGPIO36},
            {EDigitalDevices::eParam2, EGPIO::eGPIO24},
			{EDigitalDevices::eParam3, EGPIO::eGPIO32},
			{EDigitalDevices::eParam4, EGPIO::eGPIO33},


			{EDigitalDevices::eParam5, EGPIO::eGPIO7},
			{EDigitalDevices::eParam6, EGPIO::eGPIO11},
			{EDigitalDevices::eParam7, EGPIO::eGPIO15},
			{EDigitalDevices::eParam8, EGPIO::eGPIO19},
			{EDigitalDevices::eParam9, EGPIO::eGPIO21},
            {EDigitalDevices::eParam10, EGPIO::eGPIO31},
			{EDigitalDevices::eParam11, EGPIO::eGPIO29},
            {EDigitalDevices::eParam12, EGPIO::eGPIO23}
		};

		static std::map<Controller::Devices::EAnalog, std::pair<std::pair<ESPIDevices, int>, ESPIChannel>> AnalogDivicesMap = {

			{EAnalog::eParam1, { {ESPIDevices::eSPI1, 0}, ESPIChannel::eCH0}},
			{EAnalog::eParam2, {{ESPIDevices::eSPI1, 0}, ESPIChannel::eCH1}},
			{EAnalog::eParam3, {{ESPIDevices::eSPI1, 0}, ESPIChannel::eCH2}},
			{EAnalog::eParam4, {{ESPIDevices::eSPI1, 0}, ESPIChannel::eCH3}},

			{EAnalog::eParam5, {{ESPIDevices::eSPI1, 1}, ESPIChannel::eCH0}},

		};
	}
}
