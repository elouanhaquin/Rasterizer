#pragma once

#include "Vec3.h"

namespace Maths
{
	class Vec4
	{
	public:
		float x;
		float y;
		float z;
		float w;

	public:
		explicit Vec4(const float& p_x,
		              const float& p_y,
		              const float& p_z,
		              const float& p_w = 1.f);
		explicit Vec4(const Vec3& p_vector,
		              const float& p_w = 1.f);
		~Vec4();

		float GetMagnitude() const;

		void Normalize();
		void Homogenize();

		Vec4 operator+(const Vec4& p_vector) const;
		Vec4 operator*(const float& p_scalar) const;

		Vec3 ToVec3() const;
	};
}
