#pragma once

#include "LrssnEngine/Core/Layer.h"
#include "LrssnEngine/Events/ApplicationEvent.h"
#include "LrssnEngine/Events/KeyEvent.h"
#include "LrssnEngine/Events/MouseEvent.h"

namespace LrssnEngine {

	class LrssnEngine_API ImGuiLayer : public Layer 	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float mTime = 0.0f;
	};

}