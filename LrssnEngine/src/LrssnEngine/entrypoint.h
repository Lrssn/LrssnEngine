#pragma once

#ifdef LE_PLATFORM_WINDOWS

extern LrssnEngine::Application* LrssnEngine::createApplication();

int main(int argc, char** argv){
    auto app = LrssnEngine::createApplication();
    app->run();
    delete app;
    return 0;// TODO: needed?
}
#endif