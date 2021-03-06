#pragma once
#include "Drifter/Core/Base.h"

#pragma warning(push, 4)        
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)


namespace Drifter {
	class Log {
	public:
		static void Init();
		inline static Ref<spdlog::logger>& GetCoreLoggger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLoggger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;

	};
}


#define DF_CORE_ERROR(...) :: Drifter::Log::GetCoreLoggger()->error(__VA_ARGS__)
#define DF_CORE_WARNING(...) :: Drifter::Log::GetCoreLoggger()->warn(__VA_ARGS__)
#define DF_CORE_INFO(...) :: Drifter::Log::GetCoreLoggger()->info(__VA_ARGS__)
#define DF_CORE_TRACE(...) :: Drifter::Log::GetCoreLoggger()->trace(__VA_ARGS__)
#define DF_CORE_Fatal(...) :: Drifter::Log::GetCoreLoggger()->fatal(__VA_ARGS__)

#define DF_CLIENT_ERROR(...) :: Drifter::Log::GetCoreLoggger()->error(__VA_ARGS__)
#define DF_CLIENT_WARNING(...) :: Drifter::Log::GetCoreLoggger()->warn(__VA_ARGS__)
#define DF_CLIENT_INFO(...) :: Drifter::Log::GetCoreLoggger()->info(__VA_ARGS__)
#define DF_CLIENT_TRACE(...) :: Drifter::Log::GetCoreLoggger()->trace(__VA_ARGS__)
#define DF_CLIENT_Fatal(...) :: Drifter::Log::GetCoreLoggger()->fatal(__VA_ARGS__)

#ifdef DF_CORE
#define DF_LOG_ERROR(...) :: Drifter::Log::GetCoreLoggger()->error(__VA_ARGS__)
#define DF_LOG_WARNING(...) :: Drifter::Log::GetCoreLoggger()->warn(__VA_ARGS__)
#define DF_LOG_INFO(...) :: Drifter::Log::GetCoreLoggger()->info(__VA_ARGS__)
#define DF_LOG_TRACE(...) :: Drifter::Log::GetCoreLoggger()->trace(__VA_ARGS__)
#define DF_LOG_Fatal(...) :: Drifter::Log::GetCoreLoggger()->fatal(__VA_ARGS__)
#else
#define DF_LOG_ERROR(...) :: Drifter::Log::GetClientLoggger()->error(__VA_ARGS__)
#define DF_LOG_WARNING(...) :: Drifter::Log::GetClientLoggger()->warn(__VA_ARGS__)
#define DF_LOG_INFO(...) :: Drifter::Log::GetClientLoggger()->info(__VA_ARGS__)
#define DF_LOG_TRACE(...) :: Drifter::Log::GetClientLoggger()->trace(__VA_ARGS__)
#define DF_LOG_Fatal(...) :: Drifter::Log::GetClientLoggger()->fatal(__VA_ARGS__)

#endif