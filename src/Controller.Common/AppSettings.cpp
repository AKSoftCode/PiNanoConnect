#include "AppSettings.hpp"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include "exceptxx/TryCatch.h"
#include "ini-parser/INI.h"

using namespace Controller;
using namespace Settings;

using json = nlohmann::json;

namespace {

    json ReadConfigJson(std::string& configFileName)
	{
		//Read json
        std::ifstream f(configFileName);
		json data;
		if (f.good())
		{
			data = json::parse(f);
		}
		return data;
	}

	void WriteConfigJson(std::string configFileName, json jsonData, bool bCreateWithDefault = false)
	{
		std::string bkpFileName = "Bkp.json";
		{
			if (!bCreateWithDefault)
			{
				std::filesystem::rename(configFileName, bkpFileName);
			}

			std::ofstream o(configFileName);
			o << std::setw(4) << jsonData << std::endl;
		}

		if (std::filesystem::exists(bkpFileName))
		{
			std::filesystem::remove(bkpFileName);
		}
	}
}

IAppSettings& getAppSettingsInstance()
{
	static AppSettings appSettings;
	return appSettings;
}


AppSettings::AppSettings()
{
	//Read ini file
	INI::PARSE_FLAGS = INI::PARSE_COMMENTS_ALL | INI::PARSE_COMMENTS_SLASH | INI::PARSE_COMMENTS_HASH;
	INI::SAVE_FLAGS = INI::SAVE_PRUNE | INI::SAVE_PADDING_SECTIONS | INI::SAVE_SPACE_SECTIONS | INI::SAVE_SPACE_KEYS | INI::SAVE_TAB_KEYS | INI::SAVE_SEMICOLON_KEYS;

	INI iniConfig("Controller.ini", true);  // Assign ini file and parse

	iniConfig.select("Application");
	auto configPath = iniConfig.get("ConfigPath", "");

	SPDLOG_INFO("Config Path : {} ", configPath);
	std::string currentOutDir = std::filesystem::current_path().string();
    configPath_ = currentOutDir + "/" + configPath + "/ControllerConfig.json";

	bool isTestMode = iniConfig.get("TestMode", "false") == "true";
	SPDLOG_INFO("Test Mode : {} ", isTestMode);
	testMode_ = isTestMode;

	if (std::filesystem::exists(configPath_))
	{
		readConfigValues();

		serverAddresss_ = iniConfig.get("ServerAddress", "");
	}
	else
	{
		SPDLOG_CRITICAL("Config file not found!!");
	}
}

const std::any AppSettings::getConfigValue(std::string key) noexcept
{
	EX_TRY(ex)
	{
		
	}
	EX_CATCH(ex);

	if (ex)
	{
		SPDLOG_ERROR("Exception : {} ", ex->what());
	}

	return "";
}


const void AppSettings::setConfigValue(std::string key, std::any value) noexcept
{
	EX_TRY(ex)
	{
		auto jsonConfig = ReadConfigJson(configPath_);

		WriteConfigJson(configPath_, jsonConfig);
	}
	EX_CATCH(ex);

	if (ex)
	{
		SPDLOG_ERROR("Exception : {} ", ex->what());
	}
}

const std::string AppSettings::getServerAddress() const noexcept
{
	return serverAddresss_;
}

const bool AppSettings::getTestMode() const noexcept
{
	return testMode_;
}

void AppSettings::readConfigValues()
{
	EX_TRY(ex)
	{
		// Read json file
		auto jsonData = ReadConfigJson(configPath_);

	
	}
	EX_CATCH(ex);

	if (ex)
	{
		SPDLOG_ERROR("Exception : {} ", ex->what());
	}
}
