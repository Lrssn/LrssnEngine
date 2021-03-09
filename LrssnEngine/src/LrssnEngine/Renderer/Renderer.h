#pragma once

#include "LrssnEngine/Renderer/RenderCommand.h"

#include "LrssnEngine/Renderer/OrthographicCamera.h"
#include "LrssnEngine/Renderer/Shader.h"

namespace LrssnEngine {

	class Renderer 	{
	public:
		static void Init();
		static void Renderer::Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	
	private:
	struct SceneData 		{
		glm::mat4 ViewProjectionMatrix;
	};

	static Scope<SceneData> s_mSceneData;
	};
}