#pragma once

// TODO: Figure out why this had to be added after including spdlog/spdlog.h -> Would not build otherwise
#pragma warning(disable : 4996)

#include "Core.h"
#include "spdlog/spdlog.h"
// Ouput stream operator for spdlog
#include "spdlog/fmt/ostr.h"

namespace Nova {
	
	enum LOG_LEVEL
	{
		TRACE,
		DEBUG,
		INFO,
		WARNING,
		ERR,
		CRITICAL,
		OFF
	};

	class NOVA_API Log
	{
	public:
		static void Init();

		static void SetCoreLoggerLevel(LOG_LEVEL level);
		static void SetClientLoggerLevel(LOG_LEVEL level);

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// TODO: Add define to strip these macros when building "for real"

// Set CoreLogger logging level
#define NOVA_CORE_SET_LOG_LEVEL(LOG_LEVEL) ::Nova::Log::SetCoreLoggerLevel(LOG_LEVEL)

// CoreLogger logging macros
#define NOVA_CORE_TRACE(...)   ::Nova::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NOVA_CORE_INFO(...)    ::Nova::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NOVA_CORE_WARN(...)    ::Nova::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NOVA_CORE_ERROR(...)   ::Nova::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NOVA_CORE_FATAL(...)   ::Nova::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Set ClientLogger logging level
#define NOVA_SET_LOG_LEVEL(LOG_LEVEL) ::Nova::Log::SetClientLoggerLevel(LOG_LEVEL)

// ClientLogger logging macros
#define NOVA_TRACE(...)        ::Nova::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NOVA_INFO(...)         ::Nova::Log::GetClientLogger()->info(__VA_ARGS__)
#define NOVA_WARN(...)         ::Nova::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NOVA_ERROR(...)        ::Nova::Log::GetClientLogger()->error(__VA_ARGS__)
#define NOVA_FATAL(...)        ::Nova::Log::GetClientLogger()->fatal(__VA_ARGS__)

