#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace Flow {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> m_CoreLogger;
		static std::shared_ptr<spdlog::logger> m_ClientLogger;
	};
}

// Core log macros
#define FLOW_CORE_TRACE(...) ::Flow::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FLOW_CORE_INFO(...) ::Flow::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FLOW_CORE_WARN(...) ::Flow::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FLOW_CORE_ERROR(...) ::Flow::Log::GetCoreLogger()->error(__VA_ARGS__)

// Client log macros
#define FLOW_CLIENT_TRACE(...) ::Flow::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FLOW_CLIENT_INFO(...) ::Flow::Log::GetClientLogger()->info(__VA_ARGS__)
#define FLOW_CLIENT_WARN(...) ::Flow::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FLOW_CLIENT_ERROR(...) ::Flow::Log::GetClientLogger()->error(__VA_ARGS__)