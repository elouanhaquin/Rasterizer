#include <iostream>

#include "../../includes/World/Entity.h"

using namespace World;

Entity::Entity(Mesh* p_mesh,
               const Mat4& p_transform) : m_mesh {p_mesh},
                                          m_transform {p_transform}
{
	std::cout << "Entity created" << std::endl;
}

Entity::~Entity()
{
	std::cout << "Entity destroyed" << std::endl;
}

void Entity::SetTransform(const Mat4& p_transform)
{
	m_transform = p_transform;
}

const Mesh* Entity::GetMesh() const { return m_mesh; }

const Mat4& Entity::GetTransform() const { return m_transform; }
