#pragma once
#include "LrssnEngine/Core/Base.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>


namespace LrssnEngine{
    class Log{
    public:
        static void init();

        static Ref<spdlog::logger>& GetCoreLogger(){ return s_CoreLogger;};
        static Ref<spdlog::logger>& GetClientLogger(){ return s_ClientLogger;};
    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;

    };
}

//core log macros
#define LE_CORE_TRACE(...)  ::LrssnEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LE_CORE_INFO(...)   ::LrssnEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LE_CORE_WARN(...)   ::LrssnEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LE_CORE_ERROR(...)  ::LrssnEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LE_CORE_CRITICAL(...)  ::LrssnEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

//client log macros
#define LE_TRACE(...)       ::LrssnEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LE_INFO(...)        ::LrssnEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define LE_WARN(...)        ::LrssnEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LE_ERROR(...)       ::LrssnEngine::Log::GetlienteLogger()->error(__VA_ARGS__)
#define LE_CRITICAL(...)       ::LrssnEngine::Log::GetlienteLogger()->critical(__VA_ARGS__)