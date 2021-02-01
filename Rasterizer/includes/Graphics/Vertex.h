#pragma once

#include "../Maths/Vec3.h"
#include "Color.h"

using namespace Maths;

namespace Graphics
{
	class Vertex
	{
	private:
		Vec3 m_position;
		Vec3 m_normal;

		Color m_color;

	public:
		explicit Vertex(const Vec3& p_position,
		                const Vec3& p_normal = Vec3(0, 0, 0),
		                const Color& p_color = Color::White());
		~Vertex();

		void SetPosition(const Vec3& p_position);
		void SetNormal(const Vec3& p_normal);

		const Vec3& GetPosition() const;
		const Vec3& GetNormal() const;

		const Color& GetColor() const;
	};
}
