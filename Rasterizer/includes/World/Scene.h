#pragma once

#include <vector>

#include "Entity.h"
#include "Light.h"

namespace World
{
	class Scene
	{
	private:
		std::vector<Entity> m_entities;
		std::vector<Light> m_lights;

	public:
		Scene();
		~Scene();

		void AddEntity(Entity&& p_entity);
		void AddLight(Light&& p_light);

		std::vector<Entity>& GetEntities();
		std::vector<Light>& GetLights();
	};
}
