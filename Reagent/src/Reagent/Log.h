#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"

namespace rg {
	
	class RG_API Log
	{

	public:
		// initialize the loggers and create spreate thread of execution 
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		// define a shared logger memory space for reagent and CLIENT logger
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// create CORE_LOGGER macro to make writing simpler (order of severity)
#define RG_CORE_TRACE(...)		::rg::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RG_CORE_INFO(...)		::rg::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RG_CORE_WARN(...)		::rg::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RG_CORE_ERROR(...)		::rg::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RG_CORE_FATAL(...)		::rg::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// create CLIENT_LOGGER macro to make writing simpler (order of severity)
#define RG_CLIENT_TRACE(...)	::rg::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RG_CLIENT_INFO(...)		::rg::Log::GetClientLogger()->info(__VA_ARGS__)
#define RG_CLIENT_WARN(...)		::rg::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RG_CLIENT_ERROR(...)	::rg::Log::GetClientLogger()->error(__VA_ARGS__)
#define RG_CLIENT_FATAL(...)	::rg::Log::GetClientLogger()->fatal(__VA_ARGS__)
