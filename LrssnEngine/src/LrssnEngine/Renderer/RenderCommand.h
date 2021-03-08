#pragma once

#include "RendererAPI.h"

namespace LrssnEngine {

	class RenderCommand 	{
	public:
		inline static void Init() 		{
			s_mRendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color) 		{
			s_mRendererAPI->SetClearColor(color);
		}

		inline static void Clear() 		{
			s_mRendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) 		{
			s_mRendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* s_mRendererAPI;
	};

}