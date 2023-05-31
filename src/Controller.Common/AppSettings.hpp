#pragma once

#include "include/AppSettings.h"
#include "include/DataTypes.h"

namespace Controller
{
	namespace Settings
	{
		class AppSettings : public IAppSettings
		{
		public:

			explicit AppSettings();
			virtual ~AppSettings() = default;

			const std::any getConfigValue(std::string key) noexcept override;

			const void setConfigValue(std::string key, std::any value) noexcept override;

			const std::string getServerAddress() const noexcept override;

			const bool getTestMode() const noexcept override;

		private:

			void readConfigValues();

			std::string configPath_;

			std::string serverAddresss_;


			bool testMode_;

			double blowerSpeed_;

		};
	}
}
