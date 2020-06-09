#include "novapch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Nova {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("NOVA");
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		// Don't forget to set the desired LOG_LEVEL for each Logger
	}

	void Log::SetCoreLoggerLevel(LOG_LEVEL level)
	{
		switch (level)
		{
		case LOG_LEVEL::TRACE:		s_CoreLogger->set_level(spdlog::level::trace); break;
		case LOG_LEVEL::DEBUG:		s_CoreLogger->set_level(spdlog::level::debug); break;
		case LOG_LEVEL::INFO:		s_CoreLogger->set_level(spdlog::level::info); break;
		case LOG_LEVEL::WARNING:	s_CoreLogger->set_level(spdlog::level::warn); break;
		case LOG_LEVEL::ERR:		s_CoreLogger->set_level(spdlog::level::err); break;
		case LOG_LEVEL::CRITICAL:	s_CoreLogger->set_level(spdlog::level::critical); break;
		case LOG_LEVEL::OFF:		s_CoreLogger->set_level(spdlog::level::off); break;
		default: break;
		}
	}

	void Log::SetClientLoggerLevel(LOG_LEVEL level)
	{
		switch (level)
		{
		case LOG_LEVEL::TRACE:		s_ClientLogger->set_level(spdlog::level::trace); break;
		case LOG_LEVEL::DEBUG:		s_ClientLogger->set_level(spdlog::level::debug); break;
		case LOG_LEVEL::INFO:		s_ClientLogger->set_level(spdlog::level::info); break;
		case LOG_LEVEL::WARNING:	s_ClientLogger->set_level(spdlog::level::warn); break;
		case LOG_LEVEL::ERR:		s_ClientLogger->set_level(spdlog::level::err); break;
		case LOG_LEVEL::CRITICAL:	s_ClientLogger->set_level(spdlog::level::critical); break;
		case LOG_LEVEL::OFF:		s_ClientLogger->set_level(spdlog::level::off); break;
		default: break;
		}
	}

}