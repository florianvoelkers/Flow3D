#pragma once

#include <memory>

#include "spdlog/spdlog.h"

// Class for debug logging in the console using the library spdlog
// provides macros for severall logging functions
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

// Core log macros
#define FLOW_CORE_TRACE(...) ::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FLOW_CORE_INFO(...) ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FLOW_CORE_WARN(...) ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FLOW_CORE_ERROR(...) ::Log::GetCoreLogger()->error(__VA_ARGS__)

// Client log macros
#define FLOW_CLIENT_TRACE(...) ::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FLOW_CLIENT_INFO(...) ::Log::GetClientLogger()->info(__VA_ARGS__)
#define FLOW_CLIENT_WARN(...) ::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FLOW_CLIENT_ERROR(...) ::Log::GetClientLogger()->error(__VA_ARGS__)