#pragma once
#include "LrssnEngine/core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"


namespace LrssnEngine{
    class LrssnEngine_API Log
    {
    public:
        static void init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){ return s_CoreLogger;};
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){ return s_ClientLogger;};
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;

    };
}

//core log macros
#define LE_CORE_TRACE(...)  ::LrssnEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LE_CORE_INFO(...)   ::LrssnEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LE_CORE_WARN(...)   ::LrssnEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LE_CORE_ERROR(...)  ::LrssnEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LE_CORE_FATAL(...)  ::LrssnEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//client log macros
#define LE_TRACE(...)       ::LrssnEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LE_INFO(...)        ::LrssnEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define LE_WARN(...)        ::LrssnEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LE_ERROR(...)       ::LrssnEngine::Log::GetlienteLogger()->error(__VA_ARGS__)
#define LE_FATAL(...)       ::LrssnEngine::Log::GetlienteLogger()->fatal(__VA_ARGS__)