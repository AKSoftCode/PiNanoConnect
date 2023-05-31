#pragma once

#include "include/IDeviceInterface.h"
#include <AppSettings.h>

namespace Controller
{
	namespace HAL
	{
		class DeviceInterface : public IDeviceInterface
		{
			using CmdStatusDelegate = delegate<void, uint8_t, bool>;
			CmdStatusDelegate cmdDelegate;

			IHAL& jestsonDriver_;
			Settings::IAppSettings& appSettings_;

			bool setParam1(bool bStatus) noexcept;
			bool getParam1Status() const noexcept;;

			bool setParam2(bool bStatus) noexcept;
			bool getParam2Status() const noexcept;

			bool setParam3(bool bStatus) noexcept;
			bool getParam3Status() const noexcept;

			bool setParam4(bool bStatus) noexcept;
			bool getParam4Status() const noexcept;

			bool setParam5(bool bStatus) noexcept;
			bool getParam5Status() const noexcept;

			bool setParam6(bool bStatus) noexcept;
			bool getParam6Status() const noexcept;

			bool setParam7(bool bStatus) noexcept;
			bool getParam7Status() const noexcept;

			bool setParam8(bool bStatus) noexcept;
			bool getParam8Status() const noexcept;

			bool setParam9(bool bStatus) noexcept;
			bool getParam9Status() const noexcept;

			bool setParam10(bool bStatus) noexcept;
			bool getParam10Status() const noexcept;

			bool setParam11(bool bStatus) noexcept;
			bool getParam11Status() const noexcept;

			bool setParam12(bool bStatus) noexcept;
			bool getParam12Status() const noexcept;

			double getAnalogParam1Value() const noexcept;

			double getAnalogParam2Value() const noexcept;

			double getAnalogParam3Value() const noexcept;

			double getAnalogParam4Value() const noexcept;

			double getAnalogParam5Value() const noexcept;
			bool setParam4SpeedValue(double bValue) noexcept;

            bool goToSafeMode() noexcept;

		public:
			DeviceInterface();

			virtual std::any deviceOperation(std::string jsonParam) noexcept override;

			virtual void registerEventCallback(CmdStatusDelegate callback) noexcept override;
		};
	}
}

