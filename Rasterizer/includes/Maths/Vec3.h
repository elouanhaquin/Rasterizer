#pragma once

namespace Maths
{
	class Vec3
	{
	public:
		float x;
		float y;
		float z;

	public:
		explicit Vec3(const float& p_x,
		              const float& p_y,
		              const float& p_z);
		~Vec3();

		float GetMagnitude() const;

		void Normalize();

		Vec3 operator+(const Vec3& p_vector) const;
		Vec3 operator-(const Vec3& p_vector) const;
		Vec3 operator*(const float& p_scalar) const;

		float operator*(const Vec3& p_vector) const;
	};
}
