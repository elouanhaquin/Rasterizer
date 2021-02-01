#include <iostream>

#include "../../includes/World/Scene.h"

using namespace World;

Scene::Scene()
{
	std::cout << "Scene created" << std::endl;
}

Scene::~Scene()
{
	for (size_t i = 0; i < m_entities.size(); ++i)
		delete m_entities[i].GetMesh();

	std::cout << "Scene detroyed" << std::endl;
}

void Scene::AddEntity(Entity&& p_entity)
{
	m_entities.push_back(p_entity);
}

void Scene::AddLight(Light&& p_light)
{
	m_lights.push_back(p_light);
}

std::vector<Entity>& Scene::GetEntities() { return m_entities; }
std::vector<Light>& Scene::GetLights() { return m_lights; }
