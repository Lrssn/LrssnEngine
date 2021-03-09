#include "lepch.h"
#include "LrssnEngine/Core/Application.h"
#include "LrssnEngine/Core/Input.h"

#include "LrssnEngine/Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace LrssnEngine{

    Application* Application::s_mInstance = nullptr;

    //public functions
    Application::Application() {
        LE_PROFILE_FUNCTION();
        LE_CORE_ASSERT(!s_mInstance, "Application already exists!");
        s_mInstance = this;
        mWindow = Window::Create();
        mWindow->SetEventCallback(LE_BIND_EVENT_FN(Application::OnEvent));
        Renderer::Init();
        mImGuiLayer = new ImGuiLayer();
        PushOverlay(mImGuiLayer);
    }

    Application::~Application(){
        LE_PROFILE_FUNCTION();
        Renderer::Shutdown();
    }

    void Application::run(){
        LE_PROFILE_FUNCTION();
        while(mRunning){
            LE_PROFILE_SCOPE("RunLoop");
            float time = (float)glfwGetTime();
            Timestep timestep = time - mLastFrameTime;
            mLastFrameTime = time;

            if (!mMinimized) {
                LE_PROFILE_SCOPE("OnUpdate");
                for (Layer* layer : mLayerStack)
                    layer->OnUpdate(timestep);
            }
            {
                LE_PROFILE_SCOPE("OnImGuiRender");
                mImGuiLayer->Begin();
                for (Layer* layer : mLayerStack)
                    layer->OnImGuiRender();
                mImGuiLayer->End();
            }
            mWindow->OnUpdate();
		}
    }

    void Application::OnEvent(Event& e) 	{
        LE_PROFILE_FUNCTION();
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(LE_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(LE_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = mLayerStack.rbegin(); it != mLayerStack.rend(); ++it) {
            (*it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::PushLayer(Layer* layer) 	{
        LE_PROFILE_FUNCTION();
        mLayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer) 	{
        LE_PROFILE_FUNCTION();
        mLayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    //private functions
    bool Application::OnWindowClose(WindowCloseEvent& e) 	{
        LE_PROFILE_FUNCTION();
        mRunning = false;
        return true;
    }
    bool Application::OnWindowResize(WindowResizeEvent& e) 	{
        LE_PROFILE_FUNCTION();
        if (e.GetWidth() == 0 || e.GetHeight() == 0) 		{
            mMinimized = true;
            return false;
        }

        mMinimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }
} // namespace LrssnEngine