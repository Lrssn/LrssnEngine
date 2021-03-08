#include "lepch.h"
#include "log.h"
namespace LrssnEngine{
    Ref<spdlog::logger> Log::s_CoreLogger;
    Ref<spdlog::logger> Log::s_ClientLogger;

    void Log::init(){
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("LrssnEngine");
        s_CoreLogger->set_level(spdlog::level::trace);
        s_ClientLogger = spdlog::stdout_color_mt("Application");
        s_ClientLogger->set_level(spdlog::level::trace);


    }
}