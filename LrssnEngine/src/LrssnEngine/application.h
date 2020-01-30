#pragma once
#include "core.h"
#include "Events/applicationEvent.h"
#include "log.h"
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