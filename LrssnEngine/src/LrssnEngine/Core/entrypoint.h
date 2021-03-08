#pragma once

#ifdef LE_PLATFORM_WINDOWS

extern LrssnEngine::Application* LrssnEngine::createApplication();

int main(int argc, char** argv){
    LrssnEngine::Log::init();
    LE_CORE_WARN("warning from core");
    LE_TRACE("trace from client");

    auto app = LrssnEngine::createApplication();
    app->run();
    delete app;
    return 0;// TODO: needed?
}
#endif