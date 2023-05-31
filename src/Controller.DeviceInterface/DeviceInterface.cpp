
#include "dylib.hpp"

#include "DeviceInterface.hpp"
#include <string>
#include "include/IHAL.h"
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/async.h>

#include <DataTypes.h>
#include "exceptxx/TryCatch.h"

using json = nlohmann::json;

using namespace Controller;
using namespace Settings;
using namespace HAL;
using namespace Devices;
using namespace std::chrono_literals;

namespace
{
    std::shared_ptr<spdlog::logger> cmdLogger;
    std::shared_ptr<spdlog::logger> updateLogger;

    void initLoger()
    {
		EX_TRY(ex)
		{
			spdlog::init_thread_pool(10240, 5);
			static auto tp = spdlog::thread_pool();
			auto rotating_sink_updates = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("Logs//Controller_Updates.logs", 1024 * 1024 * 10, 3);
			std::vector<spdlog::sink_ptr> sinksUpdates{  rotating_sink_updates };
			updateLogger = std::make_shared<spdlog::logger>("Controller_Updates", sinksUpdates.begin(), sinksUpdates.end());
			spdlog::register_logger(updateLogger);

			auto rotating_sink_commands = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("Logs//Controller_Commands.logs", 1024 * 1024 * 10, 3);
			std::vector<spdlog::sink_ptr> sinksCommands{ rotating_sink_commands };
			cmdLogger = std::make_shared<spdlog::logger>("Controller_Commands", sinksCommands.begin(), sinksCommands.end());
			spdlog::register_logger(cmdLogger);

            cmdLogger->flush_on(spdlog::level::debug);
            cmdLogger->set_level(spdlog::level::trace);
            updateLogger->flush_on(spdlog::level::debug);
            updateLogger->set_level(spdlog::level::trace);
		}
		EX_CATCH(ex);

		if (ex)
		{
			SPDLOG_ERROR("Exception : {} ", ex->what());
		}
    }

	IHAL& initJetsonDriver()
	{
		EX_TRY(ex)
		{
			static std::unique_ptr<dylib> lib;
			std::string currentOutDir = std::filesystem::current_path().string();
			try
			{
				lib = std::make_unique<dylib>(currentOutDir, "JetsonNanoDriver");
				auto instanceFunc = lib->get_function<Controller::HAL::IHAL& ()>("Instance");
				SPDLOG_INFO("Jetson Driver Loaded.....");
				return instanceFunc();
			}
			catch (const dylib::load_error&) {
				lib = std::make_unique<dylib>(currentOutDir, "JetsonNanoSimDriver");
				auto instanceFunc = lib->get_function<Controller::HAL::IHAL& ()>("Instance");
				SPDLOG_ERROR("Jetson Driver Not found !! Loading Simulation Driver.....");
				return instanceFunc();
			}
		}
		EX_CATCH(ex);

		if (ex)
		{
			SPDLOG_ERROR("Exception : {} ", ex->what());
		}
	}

	double calculateAnalogValue(int currentCount, ADCConfig adcConfig)
	{
        double analogVal = (currentCount - adcConfig.countStart) * (100.0f - 0.0f)
                / (adcConfig.countEnd - adcConfig.countStart) + 0.0f;

		auto round_up = [](float value, int decimal_places) {
			const double multiplier = std::pow(10.0, decimal_places);
			return std::ceil(value * multiplier) / multiplier;
		};

		return round_up(analogVal, 1);
	}
}

IDeviceInterface & getDeviceInterfaceInstance()
{
	static DeviceInterface deviceInterface;
	return deviceInterface;
}

DeviceInterface::DeviceInterface() : jestsonDriver_(initJetsonDriver()), appSettings_(getAppSettingsInstance())
{
    initLoger();
}


std::any DeviceInterface::deviceOperation(std::string jsonParam) noexcept
{
	EX_TRY(ex)
	{
		json data = json::parse(jsonParam);

		std::string Operation = data["Operation"];
		auto value = data["StatusOrValue"];

		if (Operation == "setParam1")
		{
			return setParam1(value);
		}
		else if (Operation == "getParam1Status")
		{
			return getParam1Status();
		}
		else if (Operation == "setParam2")
		{
			return setParam2(value);
		}
		else if (Operation == "getParam2Status")
		{
			return getParam2Status();
		}
		else if (Operation == "setParam3")
		{
			return setParam3(value);
		}
		else if (Operation == "getParam3Status")
		{
			return getParam3Status();
		}
		else if (Operation == "setParam4")
		{
			return setParam4(value);
		}
		else if (Operation == "getParam4Status")
		{
			return getParam4Status();
		}
		else if (Operation == "setParam5")
		{
			return setParam5(value);
		}
		else if (Operation == "getParam5Status")
		{
			return getParam5Status();
		}
		else if (Operation == "setParam6")
		{
			return setParam6(value);
		}
		else if (Operation == "getParam6Status")
		{
			return getParam6Status();
		}
		else if (Operation == "setParam7")
		{
			return setParam7(value);
		}
		else if (Operation == "getParam7Status")
		{
			return getParam7Status();
		}
		else if (Operation == "setParam8")
		{
			return setParam8(value);
		}
		else if (Operation == "getParam8Status")
		{
			return getParam8Status();
		}
		else if (Operation == "setParam9")
		{
			return setParam9(value);
		}
		else if (Operation == "getParam9Status")
		{
			return getParam9Status();
		}
		else if (Operation == "setParam9")
		{
			return setParam9(value);
		}
		else if (Operation == "getParam9Status")
		{
			return getParam9Status();
		}
		else if (Operation == "setParam10")
		{
			return setParam10(value);
		}
		else if (Operation == "getParam10Status")
		{
			return getParam10Status();
		}
		else if (Operation == "setParam11")
		{
			return setParam11(value);
		}
		else if (Operation == "getParam11Status")
		{
			return getParam11Status();
		}
		else if (Operation == "setParam12")
		{
			return setParam12(value);
		}
		else if (Operation == "getParam12Status")
		{
			return getParam12Status();
		}
		else if (Operation == "getAnalogParam1Value")
		{
			return getAnalogParam1Value();
		}
		else if (Operation == "getAnalogParam2Value")
		{
			return getAnalogParam2Value();
		}
		else if (Operation == "getAnalogParam3Value")
		{
			return getAnalogParam3Value();
		}
		else if (Operation == "getAnalogParam4Value")
		{
			return getAnalogParam4Value();
		}
		else if (Operation == "getAnalogParam5Value")
		{
			return getAnalogParam5Value();
		}
		else if (Operation == "setParam4SpeedValue")
		{
			return setParam4SpeedValue(value);
		}
		else if (Operation == "goToSafeMode")
		{
			return goToSafeMode();
		}
	}
	EX_CATCH(ex);

	if (ex)
	{
		SPDLOG_ERROR("Exception : {} ", ex->what());
	}
    return true;
}

bool DeviceInterface::goToSafeMode() noexcept
{
	EX_TRY(ex)
	{
		//For Safe Mode, put everything off
		setParam1(false);
		setParam4(false);
		setParam5(false);
		setParam12(false);
		setParam6(false);

		setParam7(false);
		setParam8(false);
		setParam9(false);
		setParam10(false);
		setParam11(false);

		setParam2(false);
		setParam3(false);
	}
	EX_CATCH(ex);

	if (ex)
	{
		SPDLOG_ERROR("Exception : {} ", ex->what());
	}

    return true;
}

void DeviceInterface::registerEventCallback(CmdStatusDelegate callback) noexcept
{
	cmdDelegate = callback;
}


bool DeviceInterface::setParam1(bool bStatus) noexcept
{
    SPDLOG_LOGGER_CALL(cmdLogger, spdlog::level::debug, "Setting Param1 : {}", bStatus ? "On" : "Off");
	jestsonDriver_.writeDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam1), bStatus ? EGPIOState::eHIGH : EGPIOState::eLOW);
	return true;
}

bool DeviceInterface::getParam1Status() const noexcept
{
	auto status = jestsonDriver_.readDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam1));
    SPDLOG_LOGGER_CALL(updateLogger, spdlog::level::debug, "Param1 Status: {}", status);
	return status;
}

bool DeviceInterface::setParam4(bool bStatus) noexcept
{
    SPDLOG_LOGGER_CALL(cmdLogger,  spdlog::level::debug, "Setting Param4 : {}", bStatus ? "On" : "Off");
	jestsonDriver_.writeDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam4), bStatus ? EGPIOState::eHIGH : EGPIOState::eLOW);
	return true;
}

bool DeviceInterface::getParam4Status() const noexcept
{
	auto status = jestsonDriver_.readDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam4));
    SPDLOG_LOGGER_CALL(updateLogger,  spdlog::level::debug, "Param4 Status: {}", status);
	return status;
}

bool DeviceInterface::setParam5(bool bStatus) noexcept
{
    SPDLOG_LOGGER_CALL(cmdLogger,  spdlog::level::debug, "Setting Param5 : {}", bStatus ? "On" : "Off");
	jestsonDriver_.writeDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam5), bStatus ? EGPIOState::eHIGH : EGPIOState::eLOW);
	return true;
}

bool DeviceInterface::getParam5Status() const noexcept
{
	auto status = jestsonDriver_.readDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam5));
    SPDLOG_LOGGER_CALL(updateLogger,  spdlog::level::debug, "Param5 Status: {}", status);
	return status;
}

bool DeviceInterface::setParam12(bool bStatus) noexcept
{
    SPDLOG_LOGGER_CALL(cmdLogger,  spdlog::level::debug, "Setting Param12 : {}", bStatus ? "On" : "Off");
	jestsonDriver_.writeDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam12), bStatus ? EGPIOState::eHIGH : EGPIOState::eLOW);
	return true;
}

bool DeviceInterface::getParam12Status() const noexcept
{
	auto status = jestsonDriver_.readDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam12));
    SPDLOG_LOGGER_CALL(updateLogger,  spdlog::level::debug, "Param12 Status: {}", status);
	return status;
}

bool DeviceInterface::setParam6(bool bStatus) noexcept
{
    SPDLOG_LOGGER_CALL(cmdLogger,  spdlog::level::debug, "Setting Param6 : {}", bStatus ? "On" : "Off");
	jestsonDriver_.writeDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam6), bStatus ? EGPIOState::eHIGH : EGPIOState::eLOW);
	return true;
}

bool DeviceInterface::getParam6Status() const noexcept
{
	auto status = jestsonDriver_.readDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam6));
    SPDLOG_LOGGER_CALL(updateLogger, spdlog::level::debug, "Param6 Status: {}", status);
	return status;
}

bool DeviceInterface::setParam7(bool bStatus) noexcept
{
    SPDLOG_LOGGER_CALL(cmdLogger, spdlog::level::debug,  "Setting Param7 : {}", bStatus ? "On" : "Off");
	jestsonDriver_.writeDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam7), bStatus ? EGPIOState::eHIGH : EGPIOState::eLOW);
	return true;
}

bool DeviceInterface::getParam7Status() const noexcept
{
	auto status = jestsonDriver_.readDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam7));
    SPDLOG_LOGGER_CALL(updateLogger,  spdlog::level::debug, "Param7 Status: {}", status);
	return status;
}

bool DeviceInterface::setParam8(bool bStatus) noexcept
{
    SPDLOG_LOGGER_CALL(cmdLogger,  spdlog::level::debug, "Setting Param8 : {}", bStatus ? "On" : "Off");
	jestsonDriver_.writeDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam8), bStatus ? EGPIOState::eHIGH : EGPIOState::eLOW);
	return true;
}

bool DeviceInterface::getParam8Status() const noexcept
{
	auto status = jestsonDriver_.readDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam8));
    SPDLOG_LOGGER_CALL(updateLogger,  spdlog::level::debug, "Param8 Status: {}", status);
	return status;
}

bool DeviceInterface::setParam9(bool bStatus) noexcept
{
    SPDLOG_LOGGER_CALL(cmdLogger,  spdlog::level::debug, "Setting Param9 : {}", bStatus ? "On" : "Off");
	jestsonDriver_.writeDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam9), bStatus ? EGPIOState::eHIGH : EGPIOState::eLOW);
	return true;
}

bool DeviceInterface::getParam9Status() const noexcept
{
	auto status = jestsonDriver_.readDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam9));
    SPDLOG_LOGGER_CALL(updateLogger,  spdlog::level::debug, "Param9 Status: {}", status);
	return status;
}


bool DeviceInterface::setParam10(bool bStatus) noexcept
{
    SPDLOG_LOGGER_CALL(cmdLogger,  spdlog::level::debug, "Setting Param10 : {}", bStatus ? "On" : "Off");
	jestsonDriver_.writeDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam10), bStatus ? EGPIOState::eHIGH : EGPIOState::eLOW);
	return true;
}

bool DeviceInterface::getParam10Status() const noexcept
{
	auto status = jestsonDriver_.readDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam10));
    SPDLOG_LOGGER_CALL(updateLogger,  spdlog::level::debug, "Param10 Status: {}", status);
	return status;
}

bool DeviceInterface::setParam11(bool bStatus) noexcept
{
    SPDLOG_LOGGER_CALL(cmdLogger,  spdlog::level::debug, "Setting Param11 : {}", bStatus ? "On" : "Off");
	jestsonDriver_.writeDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam11), bStatus ? EGPIOState::eHIGH : EGPIOState::eLOW);
	return true;
}

bool DeviceInterface::getParam11Status() const noexcept
{
	auto status = jestsonDriver_.readDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam11));
    SPDLOG_LOGGER_CALL(updateLogger,  spdlog::level::debug, "Param11 Status: {}", status);
	return status;
}


bool DeviceInterface::setParam2(bool bStatus) noexcept
{
    SPDLOG_LOGGER_CALL(cmdLogger,  spdlog::level::debug, "Setting Param2 : {}", bStatus ? "On" : "Off");
	jestsonDriver_.writeDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam2), bStatus ? EGPIOState::eHIGH : EGPIOState::eLOW);
	return true;
}

bool DeviceInterface::getParam2Status() const noexcept
{
	auto status = jestsonDriver_.readDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam2));
    SPDLOG_LOGGER_CALL(updateLogger, spdlog::level::debug,  "Param2 Status: {}", status);
	return status;
}

bool DeviceInterface::setParam3(bool bStatus) noexcept
{
    SPDLOG_LOGGER_CALL(cmdLogger,  spdlog::level::debug, "Setting Param3 : {}", bStatus ? "On" : "Off");
	jestsonDriver_.writeDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam3), bStatus ? EGPIOState::eHIGH : EGPIOState::eLOW);
	return true;
}

bool DeviceInterface::getParam3Status() const noexcept
{
	auto status = jestsonDriver_.readDigitalValue(GPIODevicesMap.at(EDigitalDevices::eParam3));
    SPDLOG_LOGGER_CALL(updateLogger,  spdlog::level::debug, "Param3 Status: {}", status);
	return status;
}


double DeviceInterface::getAnalogParam1Value() const noexcept
{
    auto count = jestsonDriver_.readAnalogValue(ESPIDevices::eSPI2, ESPIChannel::eCH0);
    SPDLOG_LOGGER_CALL(updateLogger, spdlog::level::debug, "Analog Param1 Value Count: {}", count);

	return count;
}

double DeviceInterface::getAnalogParam2Value() const noexcept
{
    auto count = jestsonDriver_.readAnalogValue(ESPIDevices::eSPI2, ESPIChannel::eCH1);
    SPDLOG_LOGGER_CALL(updateLogger, spdlog::level::debug, "Analog Param2 Value Count: {}", count);
	
	return count;
}


double DeviceInterface::getAnalogParam3Value() const noexcept
{
    auto count = jestsonDriver_.readAnalogValue(ESPIDevices::eSPI2, ESPIChannel::eCH2);
    SPDLOG_LOGGER_CALL(updateLogger, spdlog::level::debug, "Analog Param3 Value Count: {}", count);

	return count;
}

double DeviceInterface::getAnalogParam4Value() const noexcept
{
    auto count = jestsonDriver_.readAnalogValue(ESPIDevices::eSPI2, ESPIChannel::eCH3);
    SPDLOG_LOGGER_CALL(updateLogger, spdlog::level::debug, "Analog Param4 Value Count: {}", count);

	return count;
}

double DeviceInterface::getAnalogParam5Value() const noexcept
{
	//auto status = jestsonDriver_.readAnalogValue(ESPIDevices::eSPI2, ESPIChannel::eCH0);
    //SPDLOG_LOGGER_CALL(updateLogger,  spdlog::level::debug, "Analog Param5: {}", status);
	return 0;
}

bool DeviceInterface::setParam4SpeedValue(double value) noexcept
{
    SPDLOG_LOGGER_CALL(cmdLogger,  spdlog::level::debug, "Setting Analog Param4 : {}", value);
    //jestsonDriver_.writeAnalogValue(ESPIDevices::eSPI2, ESPIChannel::eCH0);
	return true;
}
