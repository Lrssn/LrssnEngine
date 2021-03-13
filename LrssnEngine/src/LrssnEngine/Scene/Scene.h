#pragma once

#include "entt.hpp"

#include "LrssnEngine/Core/Timestep.h"

namespace LrssnEngine {
	class Entity;
	class Scene {
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);
	private:

		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

		entt::registry mRegistry;
		uint32_t mViewportWidth = 0, mViewportHeight = 0;

		friend class Entity;
		friend class SceneHierarchyPanel;
	};

}