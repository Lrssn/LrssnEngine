#pragma once

#include "entt.hpp"

#include "LrssnEngine/Core/Timestep.h"

namespace LrssnEngine {
	class Entity;
	class Scene 	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(Timestep ts);
	private:
		entt::registry mRegistry;
		friend class Entity;
	};

}