#pragma once
#include <string>

#include <any>

namespace Controller
{
	namespace Settings
	{
		class IAppSettings
		{
		public:

			virtual ~IAppSettings() {}

			virtual const std::any getConfigValue(std::string key) noexcept = 0;

			virtual const void setConfigValue(std::string key, std::any value) noexcept = 0;

			virtual const std::string getServerAddress() const noexcept = 0;

			virtual const bool getTestMode() const noexcept = 0;
		};
	}
}

extern "C" {
	Controller::Settings::IAppSettings& getAppSettingsInstance();
}
