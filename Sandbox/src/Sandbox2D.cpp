#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), mCameraController(1280.0f / 720.0f) {
}

void Sandbox2D::OnAttach() {
	mTex = LrssnEngine::Texture2D::Create("assets/textures/a.png");
}

void Sandbox2D::OnDetach() {
}

void Sandbox2D::OnUpdate(LrssnEngine::Timestep ts) {
	// Update
	mCameraController.OnUpdate(ts);

	// Render
	LrssnEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	LrssnEngine::RenderCommand::Clear();

	LrssnEngine::Renderer2D::BeginScene(mCameraController.GetCamera());	
	LrssnEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	LrssnEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	LrssnEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, mTex);
	LrssnEngine::Renderer2D::EndScene();
	// TODO: Add these functions - Shader::SetMat4, Shader::SetFloat4
	// std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->Bind();
	// std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(mSquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(LrssnEngine::Event& e) {
	mCameraController.OnEvent(e);
}