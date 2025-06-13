#include "rgpch.h"
#include "Log.h"
#include <memory>
#include "spdlog/sinks/stdout_color_sinks.h"

namespace rg {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	
	void Log::Init()
	{
		//pattern: color | timestamp | name of logger | log message
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("Reagent");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("Client");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}