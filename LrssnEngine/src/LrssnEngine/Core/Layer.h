#pragma once

#include "LrssnEngine/Core/Core.h"
#include "LrssnEngine/Core/Timestep.h"
#include "LrssnEngine/Events/Event.h"

namespace LrssnEngine {

	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return mDebugName; }
	protected:
		std::string mDebugName;
	};

}