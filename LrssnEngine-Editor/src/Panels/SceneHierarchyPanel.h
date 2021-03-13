#pragma once

#include "LrssnEngine/Core/Base.h"
#include "LrssnEngine/Core/Log.h"
#include "LrssnEngine/Scene/Scene.h"
#include "LrssnEngine/Scene/Entity.h"

namespace LrssnEngine {

	class SceneHierarchyPanel {
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> mContext;
		Entity mSelectionContext;
	};

}