#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), mCameraController(1280.0f / 720.0f), mSquareColor({ 0.2f, 0.3f, 0.8f, 1.0f }) {
}

void Sandbox2D::OnAttach() {
	LE_PROFILE_FUNCTION();
	mTex = LrssnEngine::Texture2D::Create("assets/textures/a.png");
}

void Sandbox2D::OnDetach() {
	LE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(LrssnEngine::Timestep ts) {
	LE_PROFILE_FUNCTION();
	// Update
		mCameraController.OnUpdate(ts);

	// Render
	LrssnEngine::Renderer2D::ResetStats();
	{
		LE_PROFILE_SCOPE("Renderer Prep");
		LrssnEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		LrssnEngine::RenderCommand::Clear();
	}
	{
		LE_PROFILE_SCOPE("Renderer Draw");
		
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		LrssnEngine::Renderer2D::BeginScene(mCameraController.GetCamera());
		LrssnEngine::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.4f, 0.2f, 0.3f, 1.0f });
		LrssnEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		LrssnEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, mSquareColor);
		LrssnEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, mTex, 10.0f);
		LrssnEngine::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, mTex, 20.0f);
		LrssnEngine::Renderer2D::EndScene();

		LrssnEngine::Renderer2D::BeginScene(mCameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f) 		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f) 			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				LrssnEngine::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		LrssnEngine::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender() {
	LE_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	auto stats = LrssnEngine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(mSquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(LrssnEngine::Event& e) {
	mCameraController.OnEvent(e);
}