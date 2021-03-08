#include <Lrssnengine.h>
#include <LrssnEngine/Core/EntryPoint.h>

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"
#include "Platform/OpenGL/OpenGLShader.h"


class ExampleLayer : public LrssnEngine::Layer {
public:
	ExampleLayer()
		: Layer("Example"), mCameraController(1280.0f / 720.0f){
		mVertexArray = LrssnEngine::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		LrssnEngine::Ref<LrssnEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(LrssnEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		LrssnEngine::BufferLayout layout = {
			{ LrssnEngine::ShaderDataType::Float3, "a_Position" },
			{ LrssnEngine::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		mVertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		LrssnEngine::Ref<LrssnEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(LrssnEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		mVertexArray->SetIndexBuffer(indexBuffer);

		mSquareVA = LrssnEngine::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		LrssnEngine::Ref<LrssnEngine::VertexBuffer> squareVB;
		squareVB.reset(LrssnEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ LrssnEngine::ShaderDataType::Float3, "a_Position" },
			{ LrssnEngine::ShaderDataType::Float2, "a_TexCoord" }
			});
		mSquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		LrssnEngine::Ref<LrssnEngine::IndexBuffer> squareIB;
		squareIB.reset(LrssnEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		mSquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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

		mShader = LrssnEngine::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		mFlatColorShader = LrssnEngine::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
		
		auto textureShader = mShaderLibrary.Load("assets/shaders/texture.glsl");


		mTexture = LrssnEngine::Texture2D::Create("assets/textures/a.png");
		mTexture2 = LrssnEngine::Texture2D::Create("assets/textures/b.png");

		std::dynamic_pointer_cast<LrssnEngine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<LrssnEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(LrssnEngine::Timestep ts) override 	{
		// update
		mCameraController.OnUpdate(ts);
		// Render
		LrssnEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		LrssnEngine::RenderCommand::Clear();

		LrssnEngine::Renderer::BeginScene(mCameraController.GetCamera());
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<LrssnEngine::OpenGLShader>(mFlatColorShader)->Bind();
		std::dynamic_pointer_cast<LrssnEngine::OpenGLShader>(mFlatColorShader)->UploadUniformFloat3("u_Color", mSquareColor);


		for (int y = 0; y < 20; y++) 		{
			for (int x = 0; x < 20; x++) 			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				LrssnEngine::Renderer::Submit(mFlatColorShader, mSquareVA, transform);
			}
		}
		auto textureShader = mShaderLibrary.Get("texture");
		mTexture->Bind();
		LrssnEngine::Renderer::Submit(textureShader, mSquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		mTexture2->Bind();
		LrssnEngine::Renderer::Submit(textureShader, mSquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		LrssnEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override 	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(mSquareColor));
		ImGui::End();
	}

	void OnEvent(LrssnEngine::Event& e) override 	{
		mCameraController.OnEvent(e);
	}
	private:
		LrssnEngine::ShaderLibrary mShaderLibrary;
		LrssnEngine::Ref<LrssnEngine::Shader> mShader;
		LrssnEngine::Ref<LrssnEngine::Shader> mFlatColorShader;
		
		LrssnEngine::Ref<LrssnEngine::VertexArray> mVertexArray;
		LrssnEngine::Ref<LrssnEngine::VertexArray> mSquareVA;

		LrssnEngine::Ref<LrssnEngine::Texture2D> mTexture, mTexture2;
		glm::vec3 mSquareColor = { 0.2f, 0.3f, 0.8f };

		LrssnEngine::OrthographicCameraController mCameraController;
};

class Sandbox : public LrssnEngine::Application{
public:
	Sandbox(){
		PushLayer(new Sandbox2D());
	};
	~Sandbox(){};

};

LrssnEngine::Application* LrssnEngine::createApplication(){
	return new Sandbox();
}