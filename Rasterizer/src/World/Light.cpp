#include <iostream>

#include "../../includes/World/Light.h"

using namespace World;

Light::Light(const Vec3& p_position,
             const float& p_ambiantComponent,
             const float& p_diffuseComponent,
             const float& p_specularComponent) : m_position {p_position},
                                                 m_ambiantComponent {p_ambiantComponent},
                                                 m_diffuseComponent {p_diffuseComponent},
                                                 m_specularComponent {p_specularComponent}
{
	std::cout << "Light created" << std::endl;
}

Light::~Light()
{
	std::cout << "Light destroyed" << std::endl;
}

void Light::SetPosition(const Vec3& p_vector)
{
	m_position = p_vector;
}

const Vec3& Light::GetPosition() const { return m_position; }

const float& Light::GetAmbiantComponent() const { return m_ambiantComponent; }
const float& Light::GetDiffuseComponent() const { return m_diffuseComponent; }
const float& Light::GetSpecularComponent() const { return m_specularComponent; }
