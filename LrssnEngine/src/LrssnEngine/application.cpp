#include "lepch.h"
#include "application.h"
#include "Input.h"
#include "LrssnEngine/Renderer/Renderer.h"

namespace LrssnEngine
{
    #define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::s_mInstance = nullptr;

    //public functions
    Application::Application(){
        LE_CORE_ASSERT(!s_mInstance, "Application already exists!");
        s_mInstance = this;
        mWindow = std::unique_ptr<Window>(Window::Create());
        mWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
        
        mImGuiLayer = new ImGuiLayer();
        PushOverlay(mImGuiLayer);

        mVertexArray.reset(VertexArray::Create());

        float vertices[3 * 7] = {
              -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
               0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
               0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);
        mVertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        mVertexArray->SetIndexBuffer(indexBuffer);

        mSquareVA.reset(VertexArray::Create());

        float squareVertices[3 * 4] = {
              -0.75f, -0.75f, 0.0f,
               0.75f, -0.75f, 0.0f,
               0.75f,  0.75f, 0.0f,
              -0.75f,  0.75f, 0.0f
        };

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" }
            });
        mSquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        mSquareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
            out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
                v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
            in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
			}
		)";

        mShader.reset(new Shader(vertexSrc, fragmentSrc));

        std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

        std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

        mBlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    Application::~Application(){
    }

    void Application::run(){
        while(mRunning){
            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            RenderCommand::Clear();

            Renderer::BeginScene();


            mBlueShader->Bind();
            Renderer::Submit(mSquareVA);

            mShader->Bind();
            Renderer::Submit(mVertexArray);

            Renderer::EndScene();

            for (Layer* layer : mLayerStack)
                layer->OnUpdate();
            
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
} // namespace LrssnEngine