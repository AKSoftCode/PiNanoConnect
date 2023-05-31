#pragma once
#include <DevicesList.h>
#include <DataTypes.h>

namespace Controller
{
	namespace Model
	{
		class IDeviceActions
		{
		public:
            virtual bool goToSafeMode() noexcept = 0;

			virtual bool setParam1(bool bStatus) noexcept = 0;
			virtual bool getParam1Status() const noexcept = 0;


			virtual bool setParam2(bool bStatus) noexcept = 0;
			virtual bool getParam2Status() const noexcept = 0;

			virtual bool setParam3(bool bStatus) noexcept = 0;
			virtual bool getParam3Status() const noexcept = 0;

			virtual bool setParam4(bool bStatus) noexcept = 0;
			virtual bool getParam4Status() const noexcept = 0;

			virtual bool setParam5(bool bStatus) noexcept = 0;
			virtual bool getParam5Status() const noexcept = 0;

			virtual bool setParam6(bool bStatus) noexcept = 0;
			virtual bool getParam6Status() const noexcept = 0;

			virtual bool setParam7(bool bStatus) noexcept = 0;
			virtual bool getParam7Status() const noexcept = 0;

			virtual bool setParam8(bool bStatus) noexcept = 0;
			virtual bool getParam8Status() const noexcept = 0;

			virtual bool setParam9(bool bStatus) noexcept = 0;
			virtual bool getParam9Status() const noexcept = 0;

			virtual bool setParam10(bool bStatus) noexcept = 0;
			virtual bool getParam10Status() const noexcept = 0;

			virtual bool setParam11(bool bStatus) noexcept = 0;
			virtual bool getParam11Status() const noexcept = 0;

			virtual bool setParam12(bool bStatus) noexcept = 0;
			virtual bool getParam12Status() const noexcept = 0;


			virtual double getAnalogParam1Value() const noexcept = 0;
			virtual bool setPressureValue(double bValue) noexcept = 0;

			virtual double getAnalogParam2Value() const noexcept = 0;
			virtual bool setOxygenValue(double bValue) noexcept = 0;

			virtual double getAnalogParam3Value() const noexcept = 0;
			virtual bool setMoistureValue(double bValue) noexcept = 0;

			virtual double getAnalogParam4Value() const noexcept = 0;
			virtual bool setTempValue(double bValue) noexcept = 0;

			virtual double getAnalogParam5Value() const noexcept = 0;
			virtual bool setParam4SpeedValue(double bValue) noexcept = 0;
		};
	}
}

extern "C"
{
	Controller::Model::IDeviceActions& getProcessActionInstance();
}
