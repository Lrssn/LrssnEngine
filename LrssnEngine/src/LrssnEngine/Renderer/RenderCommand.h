#pragma once

#include "LrssnEngine/Renderer/RendererAPI.h"

namespace LrssnEngine {

	class RenderCommand {
	public:
		static void Init() {
			s_mRendererAPI->Init();
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			s_mRendererAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color) {
			s_mRendererAPI->SetClearColor(color);
		}

		static void Clear() {
			s_mRendererAPI->Clear();
		}

		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) {
			s_mRendererAPI->DrawIndexed(vertexArray, count);
		}
	private:
		static Scope<RendererAPI> s_mRendererAPI;
	};

}