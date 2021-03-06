#pragma once

#include "LrssnEngine/Core/Layer.h"
#include "LrssnEngine/Events/ApplicationEvent.h"
#include "LrssnEngine/Events/KeyEvent.h"
#include "LrssnEngine/Events/MouseEvent.h"

namespace LrssnEngine {

	class ImGuiLayer : public Layer{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;
		void Begin();
		void End();
		void BlockEvents(bool block) { mBlockEvents = block; }
		void SetDarkThemeColors();
	private:
		bool mBlockEvents = true;
		float mTime = 0.0f;
	};

}