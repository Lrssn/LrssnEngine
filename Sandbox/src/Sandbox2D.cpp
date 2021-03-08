#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), mCameraController(1280.0f / 720.0f) {
}

void Sandbox2D::OnAttach() {
	mSquareVA = LrssnEngine::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	LrssnEngine::Ref<LrssnEngine::VertexBuffer> squareVB;
	squareVB.reset(LrssnEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ LrssnEngine::ShaderDataType::Float3, "a_Position" }
		});
	mSquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	LrssnEngine::Ref<LrssnEngine::IndexBuffer> squareIB;
	squareIB.reset(LrssnEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	mSquareVA->SetIndexBuffer(squareIB);

	mFlatColorShader = LrssnEngine::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {
}

void Sandbox2D::OnUpdate(LrssnEngine::Timestep ts) {
	// Update
	mCameraController.OnUpdate(ts);

	// Render
	LrssnEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	LrssnEngine::RenderCommand::Clear();

	LrssnEngine::Renderer::BeginScene(mCameraController.GetCamera());

	std::dynamic_pointer_cast<LrssnEngine::OpenGLShader>(mFlatColorShader)->Bind();
	std::dynamic_pointer_cast<LrssnEngine::OpenGLShader>(mFlatColorShader)->UploadUniformFloat4("u_Color", mSquareColor);

	LrssnEngine::Renderer::Submit(mFlatColorShader, mSquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	LrssnEngine::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(mSquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(LrssnEngine::Event& e) {
	mCameraController.OnEvent(e);
}