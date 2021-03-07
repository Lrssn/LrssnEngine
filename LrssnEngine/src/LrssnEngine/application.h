#pragma once
#include "LrssnEngine/core.h"
#include "LrssnEngine/log.h"
#include "Window.h"
#include "LrssnEngine/LayerStack.h"
#include "LrssnEngine/Events/Event.h"
#include "LrssnEngine/Events/ApplicationEvent.h"
#include "LrssnEngine/ImGui/ImGuiLayer.h"

namespace LrssnEngine{
    class LrssnEngine_API Application
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
        std::unique_ptr<Window> mWindow;
        ImGuiLayer* mImGuiLayer;
        bool mRunning = true;
        LayerStack mLayerStack;

        static Application* s_mInstance;
    };
    Application* createApplication();
}