#pragma once

#include "Vec4.h"
#include "Mat3.h"

namespace Maths
{
	class Mat4
	{
	public:
		float data[4][4];

	public:
		Mat4();
		~Mat4();

		Mat4 operator*(const Mat4& p_matrix) const;
		Mat4 operator/(const float& p_scalar) const;
		Vec4 operator*(const Vec4& p_vector) const;

		Mat4 GetTranspose() const;
		Mat4 GetAdjoint() const;
		Mat4 GetInverse() const;
		Mat4 Div(const float& p_scalar) const;

		Mat3 Minor(const unsigned int& p_i, const unsigned int& p_j) const;

		int Sign(const unsigned int& p_i, const unsigned int& p_j) const;

		float Determinant() const;

		static Mat4 CreateTransformationMatrix(const Vec3& p_rotation,
		                                       const Vec3& p_position,
		                                       const Vec3& p_scale);
		static Mat4 CreateTranslationMatrix(const Vec3& p_translation);
		static Mat4 CreateScaleMatrix(const Vec3& p_scale);
		static Mat4 CreateXRotationMatrix(const float& p_angle);
		static Mat4 CreateYRotationMatrix(const float& p_angle);
		static Mat4 CreateZRotationMatrix(const float& p_angle);
	};
}
