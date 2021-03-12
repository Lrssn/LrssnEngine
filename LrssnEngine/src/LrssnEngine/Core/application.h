#pragma once
#include "LrssnEngine/Core/Base.h"
#include "LrssnEngine/Core/LayerStack.h"
#include "LrssnEngine/Core/Log.h"
#include "LrssnEngine/Core/Timestep.h"
#include "LrssnEngine/Core/Window.h"
#include "LrssnEngine/Events/Event.h"
#include "LrssnEngine/Events/ApplicationEvent.h"
#include "LrssnEngine/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);
namespace LrssnEngine{
    class Application
    {
    public:
        Application(const std::string& name);
        virtual ~Application();
        void Close();
        ImGuiLayer* GetImGuiLayer() { return mImGuiLayer; }
        void OnEvent(Event& e);
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer); 
        
        Window& GetWindow() { return *mWindow; }
        static Application& Get() { return *s_mInstance; }
    private:
        void run();
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
        Scope<Window> mWindow;
        ImGuiLayer* mImGuiLayer;
        bool mRunning = true;
        bool mMinimized = false;
        LayerStack mLayerStack;
        Timestep mLastFrameTime;
        static Application* s_mInstance;
        friend int ::main(int argc, char** argv);
    };
    Application* createApplication();
}