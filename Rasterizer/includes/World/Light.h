#pragma once

#include "../Maths/Vec3.h"

using namespace Maths;

namespace World
{
	class Light
	{
	private:
		Vec3 m_position;

		float m_ambiantComponent;
		float m_diffuseComponent;
		float m_specularComponent;

	public:
		explicit Light(const Vec3& p_position,
		               const float& p_ambiantCoponent,
		               const float& p_diffuseComponent,
		               const float& p_specularComponent);
		~Light();

		void SetPosition(const Vec3& p_vector);

		const Vec3& GetPosition() const;

		const float& GetAmbiantComponent() const;
		const float& GetDiffuseComponent() const;
		const float& GetSpecularComponent() const;
	};
}
