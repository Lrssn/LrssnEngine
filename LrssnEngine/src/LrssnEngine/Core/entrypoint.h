#pragma once
#include "LrssnEngine/Core/Base.h"
#include "Hazel/Core/Application.h"

#ifdef LE_PLATFORM_WINDOWS

extern LrssnEngine::Application* LrssnEngine::createApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv){
    LrssnEngine::Log::init();
    LE_PROFILE_BEGIN_SESSION("Startup", "LrssnEngine-Profile-Startup.json");
    auto app = LrssnEngine::createApplication({ argc, argv });
    LE_PROFILE_END_SESSION();
    
    LE_PROFILE_BEGIN_SESSION("Runtime", "LrssnEngine-Profile-Runtime.json");
    app->run();
    LE_PROFILE_END_SESSION();

    LE_PROFILE_BEGIN_SESSION("Shutdown", "LrssnEngine-Profile-Shutdown.json");
    delete app;
    LE_PROFILE_END_SESSION();
}
#endif