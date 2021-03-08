#include "lepch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace LrssnEngine {

	Renderer::SceneData* Renderer::s_mSceneData = new Renderer::SceneData;
	void Renderer::Init() 	{
		RenderCommand::Init();
	}
	void Renderer::BeginScene(OrthographicCamera& camera) 	{
		s_mSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() 	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform){
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_mSceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}