#include <string>

#include "IControllerGateway.h"

#include "AppSettings.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/async.h>

using namespace Controller;
using namespace Gateway;
using namespace Settings;


void setupMultiSinkLogger()
{
    //spdlog::installCrashHandlerOnce();
    //spdlog::set_pattern("[source %s] [function %!] [line %#] %v");
    spdlog::init_thread_pool(10240, 5);
    static auto tp = spdlog::thread_pool();
    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();

    auto rotating_sink_main = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("Logs//Controller.logs", 1024 * 1024 * 10, 3);
    std::vector<spdlog::sink_ptr> sinks{ stdout_sink, rotating_sink_main };
    auto mainLogger = std::make_shared<spdlog::logger>("Controller", sinks.begin(), sinks.end());
    spdlog::register_logger(mainLogger);

    spdlog::set_default_logger(mainLogger);
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_every(std::chrono::seconds(1));
}

int main()
{
    // Setup Logger
    setupMultiSinkLogger();

    SPDLOG_INFO("Starting Server......");

    getCommsInstance().StartServer(getAppSettingsInstance().getServerAddress());
	return 0;
}
