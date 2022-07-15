#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Terran {

	class TERRAN_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define TR_CORE_TRACE(...) ::Terran::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TR_CORE_INFO(...)  ::Terran::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TR_CORE_WARN(...)  ::Terran::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TR_CORE_ERROR(...) ::Terran::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TR_CORE_FATAL(...) ::Terran::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define TR_TRACE(...) ::Terran::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TR_INFO(...)  ::Terran::Log::GetClientLogger()->info(__VA_ARGS__)
#define TR_WARN(...)  ::Terran::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TR_ERROR(...) ::Terran::Log::GetClientLogger()->error(__VA_ARGS__)
#define TR_FATAL(...) ::Terran::Log::GetClientLogger()->fatal(__VA_ARGS__)