#include "lepch.h"
#include "application.h"
#include "Input.h"
#include "LrssnEngine/Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace LrssnEngine
{
    #define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::s_mInstance = nullptr;

    //public functions
    Application::Application() {
        LE_CORE_ASSERT(!s_mInstance, "Application already exists!");
        s_mInstance = this;
        mWindow = Scope<Window>(Window::Create());
        mWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
        Renderer::Init();
        mImGuiLayer = new ImGuiLayer();
        PushOverlay(mImGuiLayer);
    }

    Application::~Application(){
    }

    void Application::run(){
        while(mRunning){
            float time = (float)glfwGetTime();
            Timestep timestep = time - mLastFrameTime;
            mLastFrameTime = time;

            if (!mMinimized) 			{
                for (Layer* layer : mLayerStack)
                    layer->OnUpdate(timestep);
            }
            
            mImGuiLayer->Begin();
            for (Layer* layer : mLayerStack)
                layer->OnImGuiRender();
            mImGuiLayer->End();
            
            mWindow->OnUpdate();
		}
    }

    void Application::OnEvent(Event& e) 	{
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = mLayerStack.end(); it != mLayerStack.begin(); ) 		{
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::PushLayer(Layer* layer) 	{
        mLayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer) 	{
        mLayerStack.PushOverlay(layer);
    }

    //private functions
    bool Application::OnWindowClose(WindowCloseEvent& e) 	{
        mRunning = false;
        return true;
    }
    bool Application::OnWindowResize(WindowResizeEvent& e) 	{
        if (e.GetWidth() == 0 || e.GetHeight() == 0) 		{
            mMinimized = true;
            return false;
        }

        mMinimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }
} // namespace LrssnEngine