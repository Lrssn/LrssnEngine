#pragma once
#include "LrssnEngine/core.h"
#include "LrssnEngine/log.h"
#include "Window.h"
#include "LrssnEngine/LayerStack.h"
#include "LrssnEngine/Events/Event.h"
#include "LrssnEngine/Events/ApplicationEvent.h"
#include "LrssnEngine/ImGui/ImGuiLayer.h"

#include "LrssnEngine/Renderer/Shader.h"
#include "LrssnEngine/Renderer/Buffer.h"
#include "LrssnEngine/Renderer/VertexArray.h"

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
        
        //temp?
        std::shared_ptr<Shader> mShader;
        std::shared_ptr<VertexArray> mVertexArray;

        std::shared_ptr<Shader> mBlueShader;
        std::shared_ptr<VertexArray> mSquareVA;

        static Application* s_mInstance;
    };
    Application* createApplication();
}