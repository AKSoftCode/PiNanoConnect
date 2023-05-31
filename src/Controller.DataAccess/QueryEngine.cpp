#include "QueryEngine.hpp"
#include "IDeviceActions.h"
#include <chrono>
#include <future>
#include <AppSettings.h>
#include <DataTypes.h>
#include <spdlog/spdlog.h>

using namespace std::chrono_literals;

using namespace Controller;
using namespace DataAccess;
using namespace Devices;
using namespace Settings;
using namespace Model;
namespace
{
std::mutex gpioCacheMutex;

std::mutex analogCacheMutex;
}

Controller::DataAccess::IQueryEngine& getQueryEngineInstance()
{
    static QueryEngine queryEngine_;
    return queryEngine_;
}


QueryEngine::QueryEngine()
{
    queryThread_ = std::async(std::launch::async, [&]() {
        return QueryThreadFunc();
    });
}

bool QueryEngine::QueryThreadFunc() noexcept
{
    auto& deviceActionInstance = getProcessActionInstance();
    while (!bExitLoop_)
    {

        auto fetchDigitalIOValues = [&](EDigitalDevices devices)
        {
            switch (devices) {
            case EDigitalDevices::eParam1:
                {
                    return deviceActionInstance.getParam3Status();
                }
            case EDigitalDevices::eParam2:
                {
                    return deviceActionInstance.getParam2Status();
                }
            case EDigitalDevices::eParam3:
                {
                    return deviceActionInstance.getParam1Status();
                }
            case EDigitalDevices::eParam4:
                {
                    return deviceActionInstance.getParam4Status();
                }

            case EDigitalDevices::eParam5:
                {
                    return deviceActionInstance.getParam5Status();
                }
            case EDigitalDevices::eParam6:
                {
                    return deviceActionInstance.getParam6Status();
                }

            case EDigitalDevices::eParam7:
                {
                    return deviceActionInstance.getParam7Status();
                }
            case EDigitalDevices::eParam8:
                {
                    return deviceActionInstance.getParam8Status();
                }

            case EDigitalDevices::eParam9:
            {
                return deviceActionInstance.getParam9Status();
            }
            case EDigitalDevices::eParam10:
                {
                    return deviceActionInstance.getParam10Status();
                }
            case EDigitalDevices::eParam11:
                {
                    return deviceActionInstance.getParam11Status();
                }

            case EDigitalDevices::eParam12:
                {
                    return deviceActionInstance.getParam12Status();
                }
            default:
                break;
            }

            return false;

        };

        auto fetchAnalogValues = [&](EAnalog analogDevices)
        {
            switch (analogDevices) {
            case EAnalog::eParam1:
                {
                    return deviceActionInstance.getAnalogParam1Value();
                }
            case EAnalog::eParam2:
                {
                    return deviceActionInstance.getAnalogParam2Value();
                }
            case EAnalog::eParam3:
                {
                    return deviceActionInstance.getAnalogParam3Value();
                }
            case EAnalog::eParam4:
                {
                    return deviceActionInstance.getAnalogParam4Value();
                }
            case EAnalog::eParam5:
                {
                    return deviceActionInstance.getAnalogParam5Value();
                }
            default:
                break;
            }
            return 0.0;
        };

        {
            std::lock_guard<std::mutex> lck(gpioCacheMutex_);
            gpioCache_.clear();
            gpioCache_.emplace(EDigitalDevices::eParam1, fetchDigitalIOValues(EDigitalDevices::eParam1));
            gpioCache_.emplace(EDigitalDevices::eParam2, fetchDigitalIOValues(EDigitalDevices::eParam2));
            gpioCache_.emplace(EDigitalDevices::eParam12, fetchDigitalIOValues(EDigitalDevices::eParam12));
            gpioCache_.emplace(EDigitalDevices::eParam3, fetchDigitalIOValues(EDigitalDevices::eParam3));
            gpioCache_.emplace(EDigitalDevices::eParam4, fetchDigitalIOValues(EDigitalDevices::eParam4));
            gpioCache_.emplace(EDigitalDevices::eParam5, fetchDigitalIOValues(EDigitalDevices::eParam5));
            gpioCache_.emplace(EDigitalDevices::eParam6, fetchDigitalIOValues(EDigitalDevices::eParam6));
            gpioCache_.emplace(EDigitalDevices::eParam7, fetchDigitalIOValues(EDigitalDevices::eParam7));
            gpioCache_.emplace(EDigitalDevices::eParam8, fetchDigitalIOValues(EDigitalDevices::eParam8));
            gpioCache_.emplace(EDigitalDevices::eParam9, fetchDigitalIOValues(EDigitalDevices::eParam9));
            gpioCache_.emplace(EDigitalDevices::eParam10, fetchDigitalIOValues(EDigitalDevices::eParam10));
            gpioCache_.emplace(EDigitalDevices::eParam11, fetchDigitalIOValues(EDigitalDevices::eParam11));

        }

        {
            std::lock_guard<std::mutex> lck(analogCacheMutex_);
            analogCache_.clear();
            analogCache_.emplace(EAnalog::eParam1, fetchAnalogValues(EAnalog::eParam1));
            analogCache_.emplace(EAnalog::eParam2, fetchAnalogValues(EAnalog::eParam2));
            analogCache_.emplace(EAnalog::eParam3, fetchAnalogValues(EAnalog::eParam3));
            analogCache_.emplace(EAnalog::eParam4, fetchAnalogValues(EAnalog::eParam4));
            analogCache_.emplace(EAnalog::eParam5, fetchAnalogValues(EAnalog::eParam5));
        }


        std::this_thread::sleep_for(500ms);
    }
    return true;
}


QueryEngine::~QueryEngine()
{
    bExitLoop_ = true;
    queryThread_.get();
}

bool QueryEngine::getDigitalIOValues(EDigitalDevices devices)  noexcept
{
    try
    {
        std::lock_guard<std::mutex> lck(gpioCacheMutex_);
        return gpioCache_.at(devices);
    }
    catch(...)
    {
       SPDLOG_ERROR("Entry not found for {}", static_cast<int>(devices));
    }
    return false;
}

double QueryEngine::getAnalogValues(EAnalog analogDevices)  noexcept
{
    try
    {
        std::lock_guard<std::mutex> lck(analogCacheMutex_);
        return analogCache_.at(analogDevices);
    }
    catch(...)
    {
       SPDLOG_ERROR("Entry not found for {}", static_cast<int>(analogDevices));
    }
    return 0.0f;
}


bool QueryEngine::getProcessState(EProcessState processType) noexcept
{
    std::lock_guard<std::mutex> lk(processStateCacheMutex_);
    return processState_[processType];
}

void QueryEngine::setProcessState(EProcessState processType, bool bState) noexcept
{
    std::lock_guard<std::mutex> lk(processStateCacheMutex_);
    processState_[processType] = bState;
}
