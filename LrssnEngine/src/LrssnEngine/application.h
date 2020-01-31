#pragma once
#include "LrssnEngine/core.h"
#include "LrssnEngine/Events/applicationEvent.h"
#include "LrssnEngine/log.h"
namespace LrssnEngine{
    class LrssnEngine_API Application
    {
    public:
        Application(/* args */);
        virtual ~Application();
        void run();
    private:
    };
    Application* createApplication();
}