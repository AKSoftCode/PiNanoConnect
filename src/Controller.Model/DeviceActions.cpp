#include "DeviceActions.hpp"

#include <nlohmann/json.hpp>

#include <future>
#include <IDeviceInterface.h>
#include <chrono>

#include <spdlog/spdlog.h>
#include "exceptxx/TryCatch.h"

#include "AppSettings.h"
using namespace std::chrono_literals;
using json = nlohmann::json;

using namespace Controller;
using namespace HAL;
using namespace Model;
using namespace DataAccess;
using namespace Settings;
namespace
{
	constexpr double tolerance_ = 0.0;
	constexpr double flushingTolerance_ = 0.0;
    std::future<void> testModeFut_;
    std::atomic_bool bExitTestMode = false;
	std::string createJsonSchema(int commandId, std::string Operation, std::any bStatusOrValue = false)
	{
		json jParams;
		jParams["CommandId"] = commandId;
		jParams["Operation"] = Operation;

		if (bStatusOrValue.type() == typeid(bool))
			jParams["StatusOrValue"] = std::any_cast<bool>(bStatusOrValue);
		else
			jParams["StatusOrValue"] = std::any_cast<double>(bStatusOrValue);

		return jParams.dump();
	}
}

IDeviceActions& getProcessActionInstance()
{
	static DeviceActions deviceAction;
	return deviceAction;
}

DeviceActions::DeviceActions() :  queryEngineInstance_(getQueryEngineInstance()), deviceInterfaceInstance_(getDeviceInterfaceInstance())
{
    goToSafeMode();

    if(getAppSettingsInstance().getTestMode())
    {
        SPDLOG_DEBUG("Test Mode Activated!!");
        testModeFut_ = std::async(std::launch::async, [&]() { testModeActivate(); });
    }
}

DeviceActions::~DeviceActions()
{
	if (testModeFut_.valid())
	{
		bExitTestMode = false;
		testModeFut_.get();
	}	
}

bool DeviceActions::goToSafeMode() noexcept
{
    SPDLOG_INFO("Putting Machine into safe Mode");
    return std::any_cast<bool>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "goToSafeMode")));
}

bool DeviceActions::testModeActivate()
{
	EX_TRY(ex)
	{
		while (!bExitTestMode)
		{
			auto timeout = 10s;
			SPDLOG_INFO("Param1 On");
			setParam1(true);
			std::this_thread::sleep_for(timeout);
			setParam1(false);
			SPDLOG_INFO("Param1 Off");
			std::this_thread::sleep_for(timeout);

			SPDLOG_INFO("Param2 On");
			setParam2(true);
			std::this_thread::sleep_for(timeout);
			setParam2(false);
			SPDLOG_INFO("Param2 Off");
			std::this_thread::sleep_for(timeout);

			SPDLOG_INFO("Param3 On");
			setParam3(true);
			std::this_thread::sleep_for(timeout);
			setParam3(false);
			SPDLOG_INFO("Param3 Off");
			std::this_thread::sleep_for(timeout);

			SPDLOG_INFO("Param4 On");
			setParam4(true);
			std::this_thread::sleep_for(timeout);
			setParam4(false);
			SPDLOG_INFO("Param4 Off");
			std::this_thread::sleep_for(timeout);

			SPDLOG_INFO("Param5 On");
			setParam5(true);
			std::this_thread::sleep_for(timeout);
			setParam5(false);
			SPDLOG_INFO("Param5 Off");

			std::this_thread::sleep_for(timeout);

			SPDLOG_INFO("Param10 On");
			setParam10(true);
			std::this_thread::sleep_for(timeout);
			setParam10(false);
			SPDLOG_INFO("Param10 Off");
			std::this_thread::sleep_for(timeout);

			SPDLOG_INFO("Param11 On");
			setParam11(true);
			std::this_thread::sleep_for(timeout);
			setParam11(false);
			SPDLOG_INFO("Param11 Off");
			std::this_thread::sleep_for(timeout);

			SPDLOG_INFO("Param6 On");
			setParam6(true);
			std::this_thread::sleep_for(timeout);
			setParam6(false);
			SPDLOG_INFO("Param6 Off");
			std::this_thread::sleep_for(timeout);

			SPDLOG_INFO("Param7 On");
			setParam7(true);
			std::this_thread::sleep_for(timeout);
			setParam7(false);
			SPDLOG_INFO("Param7 Off");
			std::this_thread::sleep_for(timeout);

			SPDLOG_INFO("Param8 On");
			setParam8(true);
			std::this_thread::sleep_for(timeout);
			setParam8(false);
			SPDLOG_INFO("Param8 Off");
			std::this_thread::sleep_for(timeout);

			SPDLOG_INFO("Param9 On");
			setParam9(true);
			std::this_thread::sleep_for(timeout);
			setParam9(false);
			SPDLOG_INFO("Param9 Off");
			std::this_thread::sleep_for(timeout);
		}
	}
	EX_CATCH(ex);

	if (ex)
	{
		SPDLOG_ERROR("Exception : {} ", ex->what());
	}

    return true;
}

bool DeviceActions::setParam1(bool bStatus) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setParam1", bStatus));
	return true;
}

bool DeviceActions::getParam1Status() const noexcept
{
	return std::any_cast<bool>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getParam1Status")));
}

bool DeviceActions::setParam2(bool bStatus) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setParam2", bStatus));
	return true;
}

bool DeviceActions::getParam2Status() const noexcept
{
	return std::any_cast<bool>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getParam2Status")));
}

bool DeviceActions::setParam3(bool bStatus) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setParam3", bStatus));
	return true;
}

bool DeviceActions::getParam3Status() const noexcept
{
	return std::any_cast<bool>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getParam3Status")));
}

bool DeviceActions::setParam4(bool bStatus) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setParam4", bStatus));
	return true;
}

bool DeviceActions::getParam4Status() const noexcept
{
	return std::any_cast<bool>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getParam4Status")));
}

bool DeviceActions::setParam5(bool bStatus) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setParam5", bStatus));
	return true;
}

bool DeviceActions::getParam5Status() const noexcept
{
	return std::any_cast<bool>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getParam5Status")));
}

bool DeviceActions::setParam10(bool bStatus) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setParam10", bStatus));
	return true;
}

bool DeviceActions::getParam10Status() const noexcept
{
	return std::any_cast<bool>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getParam10Status")));
}

bool DeviceActions::setParam11(bool bStatus) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setParam11", bStatus));
	return true;
}

bool DeviceActions::getParam11Status() const noexcept
{
	return std::any_cast<bool>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getParam11Status")));
}

bool DeviceActions::setParam12(bool bStatus) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setParam12", bStatus));
	return true;
}

bool DeviceActions::getParam12Status() const noexcept
{
	return std::any_cast<bool>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getParam12Status")));
}

bool DeviceActions::setParam6(bool bStatus) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setParam6", bStatus));
	return true;
}

bool DeviceActions::getParam6Status() const noexcept
{
	return std::any_cast<bool>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getParam6Status")));
}

bool DeviceActions::setParam7(bool bStatus) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setParam7", bStatus));
	return true;
}

bool DeviceActions::getParam7Status() const noexcept
{
	return std::any_cast<bool>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getParam7Status")));
}

bool DeviceActions::setParam8(bool bStatus) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setParam8", bStatus));
	return true;
}

bool DeviceActions::getParam8Status() const noexcept
{
	return std::any_cast<bool>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getParam8Status")));
}

bool DeviceActions::setParam9(bool bStatus) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setParam9", bStatus));
	return true;
}

bool DeviceActions::getParam9Status() const noexcept
{
	return std::any_cast<bool>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getParam9Status")));
}


double DeviceActions::getAnalogParam1Value() const noexcept
{
	return std::any_cast<double>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getAnalogParam1Value")));
}

bool DeviceActions::setPressureValue(double bValue) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setPressureValue", bValue));
	return false;
}

double DeviceActions::getAnalogParam2Value() const noexcept
{
	return std::any_cast<double>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getAnalogParam2Value")));
}

bool DeviceActions::setOxygenValue(double bValue) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setOxygenValue", bValue));
	return false;
}

double DeviceActions::getAnalogParam3Value() const noexcept
{
	return std::any_cast<double>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getAnalogParam3Value")));
}

bool DeviceActions::setMoistureValue(double bValue) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setMoistureValue", bValue));
	return false;
}

double DeviceActions::getAnalogParam4Value() const noexcept
{
	return std::any_cast<double>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getAnalogParam4Value")));
}

bool DeviceActions::setTempValue(double bValue) noexcept
{
	deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setTempValue", bValue));
	return false;
}

double DeviceActions::getAnalogParam5Value() const noexcept
{
	//return std::any_cast<double>(deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "getAnalogParam5Value")));
	return std::any_cast<double>(getAppSettingsInstance().getConfigValue("BlowerSpeed"));
}
bool DeviceActions::setParam4SpeedValue(double bValue) noexcept
{
	//deviceInterfaceInstance_.deviceOperation(createJsonSchema(1, "setParam4SpeedValue", bValue));
	getAppSettingsInstance().setConfigValue("BlowerSpeed", bValue);
	return false;
}