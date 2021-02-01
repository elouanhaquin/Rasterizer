#pragma once

#include "../Graphics/Mesh.h"
#include "../Maths/Mat4.h"

using namespace Graphics;
using namespace Maths;

namespace World
{
	class Entity
	{
	private:
		Mesh* m_mesh;

		Mat4 m_transform;

	public:
		explicit Entity(Mesh* p_mesh, const Mat4& p_transform);
		~Entity();

		void SetTransform(const Mat4& p_transform);

		const Mesh* GetMesh() const;

		const Mat4& GetTransform() const;
	};
}
