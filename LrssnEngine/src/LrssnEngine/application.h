#pragma once
#include "LrssnEngine/core.h"
#include "LrssnEngine/log.h"
#include "Window.h"
#include "LrssnEngine/LayerStack.h"
#include "LrssnEngine/Events/Event.h"
#include "LrssnEngine/Events/ApplicationEvent.h"
#include "LrssnEngine/ImGui/ImGuiLayer.h"
#include "LrssnEngine/Core/Timestep.h"

namespace LrssnEngine{
    class Application
    {
    public:
        Application(/* args */);
        virtual ~Application();
        void run();
        void OnEvent(Event& e);
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer); 
        
        inline Window& GetWindow() { return *mWindow; }
        inline static Application& Get() { return *s_mInstance; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        Scope<Window> mWindow;
        ImGuiLayer* mImGuiLayer;
        bool mRunning = true;
        LayerStack mLayerStack;
        Timestep mLastFrameTime;
        static Application* s_mInstance;
    };
    Application* createApplication();
}