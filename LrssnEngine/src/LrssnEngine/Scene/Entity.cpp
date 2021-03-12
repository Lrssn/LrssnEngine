#include "lepch.h"
#include "Entity.h"

namespace LrssnEngine {

	Entity::Entity(entt::entity handle, Scene* scene)
		: mEntityHandle(handle), mScene(scene) 	{
	}

}