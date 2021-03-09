#include "lepch.h"
#include "LrssnEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "LrssnEngine/Renderer/Renderer2D.h"

namespace LrssnEngine {

	Scope<Renderer::SceneData> Renderer::s_mSceneData = CreateScope<Renderer::SceneData>();


	void Renderer::Init() 	{
		LE_PROFILE_FUNCTION();
		RenderCommand::Init();
		Renderer2D::Init();
	}
	void Renderer::Shutdown() 	{
		Renderer2D::Shutdown();
	}
	void Renderer::OnWindowResize(uint32_t width, uint32_t height) 	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
	void Renderer::BeginScene(OrthographicCamera& camera) 	{
		s_mSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() 	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform){
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_mSceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}