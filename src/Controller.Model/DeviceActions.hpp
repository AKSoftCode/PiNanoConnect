#pragma once
#include "include/IDeviceActions.h"
#include "IQueryEngine.h"

#include <IDeviceInterface.h>

#include <atomic>
#include <future>

namespace Controller
{
	using namespace DataAccess;
	using namespace HAL;
	namespace Model
	{
		class DeviceActions : public IDeviceActions
		{
            IQueryEngine& queryEngineInstance_;
			IDeviceInterface& deviceInterfaceInstance_;

			bool testModeActivate();

			void gasInletValveCheckAlarm() noexcept;

		public:

			DeviceActions();
			~DeviceActions();

            virtual bool goToSafeMode() noexcept override;

			virtual bool setParam1(bool bStatus) noexcept override;
			virtual bool getParam1Status() const noexcept override;

			virtual bool setParam2(bool bStatus) noexcept override;
			virtual bool getParam2Status() const noexcept override;

			virtual bool setParam3(bool bStatus) noexcept override;
			virtual bool getParam3Status() const noexcept override;

			virtual bool setParam4(bool bStatus) noexcept override;
			virtual bool getParam4Status() const noexcept override;

			virtual bool setParam5(bool bStatus) noexcept override;
			virtual bool getParam5Status() const noexcept override;

			virtual bool setParam6(bool bStatus) noexcept override;
			virtual bool getParam6Status() const noexcept override;

			virtual bool setParam7(bool bStatus) noexcept override;
			virtual bool getParam7Status() const noexcept override;

			virtual bool setParam8(bool bStatus) noexcept override;
			virtual bool getParam8Status() const noexcept override;

			virtual bool setParam9(bool bStatus) noexcept override;
			virtual bool getParam9Status() const noexcept override;

			virtual bool setParam10(bool bStatus) noexcept override;
			virtual bool getParam10Status() const noexcept override;

			virtual bool setParam11(bool bStatus) noexcept override;
			virtual bool getParam11Status() const noexcept override;

			virtual bool setParam12(bool bStatus) noexcept override;
			virtual bool getParam12Status() const noexcept override;

			virtual double getAnalogParam1Value() const noexcept override;
			virtual bool setPressureValue(double bValue) noexcept override;

			virtual double getAnalogParam2Value() const noexcept override;
			virtual bool setOxygenValue(double bValue) noexcept override;

			virtual double getAnalogParam3Value() const noexcept override;
			virtual bool setMoistureValue(double bValue) noexcept override;

			virtual double getAnalogParam4Value() const noexcept override;
			virtual bool setTempValue(double bValue) noexcept override;

			virtual double getAnalogParam5Value() const noexcept override;
			virtual bool setParam4SpeedValue(double bValue) noexcept override;
		};
	}
}
