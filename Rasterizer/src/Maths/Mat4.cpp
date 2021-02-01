#define _USE_MATH_DEFINES

#include <iostream>
#include  <cmath>

#include "../../includes/Maths/Mat4.h"

using namespace Maths;

Mat4::Mat4()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			data[i][j] = 0.f;

	//	std::cout << "Mat4 created" << std::endl;
}

Mat4::~Mat4()
{
	//	std::cout << "Mat4 detroyed" << std::endl;
}

Mat4 Mat4::operator*(const Mat4& p_matrix) const
{
	Mat4 mult;

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 4; ++k)
				mult.data[i][j] += data[i][k] * p_matrix.data[k][j];

	return mult;
}

Mat4 Mat4::operator/(const float& p_scalar) const { return Div(p_scalar); }

Vec4 Mat4::operator*(const Vec4& p_vector) const
{
	return Vec4(p_vector.x * data[0][0] +
	            p_vector.y * data[0][1] +
	            p_vector.z * data[0][2] +
	            p_vector.w * data[0][3], 
				p_vector.x * data[1][0] +
	            p_vector.y * data[1][1] +
	            p_vector.z * data[1][2] +
	            p_vector.w * data[1][3], 
				p_vector.x * data[2][0] +
	            p_vector.y * data[2][1] +
	            p_vector.z * data[2][2] +
	            p_vector.w * data[2][3], 
				p_vector.x * data[3][0] +
	            p_vector.y * data[3][1] +
	            p_vector.z * data[3][2] +
	            p_vector.w * data[3][3]);
}

Mat4 Mat4::GetTranspose() const
{
	Mat4 transpose;

	for (unsigned int i = 0; i < 4; ++i)
		for (unsigned int j = 0; j < 4; ++j)
			transpose.data[i][j] = data[j][i];

	return transpose;
}

Mat4 Mat4::GetAdjoint() const
{
	Mat4 adjoint;

	for (unsigned int i = 0; i < 4; ++i)
		for (unsigned int j = 0; j < 4; ++j)
			adjoint.data[i][j] = Sign(i, j) * Minor(i, j).Determinant();

	return adjoint.GetTranspose();
}

Mat4 Mat4::GetInverse() const
{
	return GetAdjoint() / Determinant();
}

Mat4 Mat4::Div(const float& p_scalar) const
{
	Mat4 div;

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			div.data[i][j] = data[i][j] / p_scalar;

	return div;
}

Mat3 Mat4::Minor(const unsigned int& p_i, const unsigned int& p_j) const
{
	Mat3 minor;

	unsigned int i = 0, j = 0;
	for (unsigned int row = 0; row < 4; ++row)
		for (unsigned int col = 0; col < 4; ++col)
		{
			if (row != p_i && col != p_j)
			{
				minor.data[i][j++] = data[row][col];
				if (j == 3)
				{
					j = 0;
					++i;
				}
			}
		}

	return minor;
}

int Mat4::Sign(const unsigned int& p_i, const unsigned int& p_j) const
{
	return static_cast<int>(pow(-1, ((p_i + 1) + (p_j + 1))));
}

float Mat4::Determinant() const
{
	return data[0][0] * (data[1][1] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) -
			data[1][2] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) +
			data[1][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1])) -
		data[0][1] * (data[1][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) -
			data[1][2] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
			data[1][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0])) +
		data[0][2] * (data[1][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) -
			data[1][1] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
			data[1][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0])) -
		data[0][3] * (data[1][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) -
			data[1][1] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]) +
			data[1][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]));
}

Mat4 Mat4::CreateTransformationMatrix(const Vec3& p_rotation,
                                      const Vec3& p_position,
                                      const Vec3& p_scale)
{
	Mat4 transform;

	transform = CreateTranslationMatrix(p_position) *
		CreateXRotationMatrix(p_rotation.x / 180.f * static_cast<float>(M_PI)) *
		CreateYRotationMatrix(p_rotation.y / 180.f * static_cast<float>(M_PI)) *
		CreateZRotationMatrix(p_rotation.z / 180.f * static_cast<float>(M_PI)) *
		CreateScaleMatrix(p_scale);

	return transform;
}

Mat4 Mat4::CreateTranslationMatrix(const Vec3& p_translation)
{
	Mat4 translation;

	translation.data[0][0] = 1.f;
	translation.data[1][1] = 1.f;
	translation.data[2][2] = 1.f;
	translation.data[3][3] = 1.f;
	translation.data[0][3] = p_translation.x;
	translation.data[1][3] = p_translation.y;
	translation.data[2][3] = p_translation.z;

	return translation;
}

Mat4 Mat4::CreateScaleMatrix(const Vec3& p_scale)
{
	Mat4 scale;

	scale.data[0][0] = p_scale.x;
	scale.data[1][1] = p_scale.y;
	scale.data[2][2] = p_scale.z;
	scale.data[3][3] = 1.f;

	return scale;
}

Mat4 Mat4::CreateXRotationMatrix(const float& p_angle)
{
	Mat4 rotX;

	rotX.data[0][0] = 1.f;
	rotX.data[3][3] = 1.f;
	rotX.data[1][1] = cos(p_angle);
	rotX.data[1][2] = -sin(p_angle);
	rotX.data[2][1] = sin(p_angle);
	rotX.data[2][2] = cos(p_angle);

	return rotX;
}

Mat4 Mat4::CreateYRotationMatrix(const float& p_angle)
{
	Mat4 rotY;

	rotY.data[1][1] = 1.f;
	rotY.data[3][3] = 1.f;
	rotY.data[0][0] = cos(p_angle);
	rotY.data[0][2] = sin(p_angle);
	rotY.data[2][0] = -sin(p_angle);
	rotY.data[2][2] = cos(p_angle);

	return rotY;
}

Mat4 Mat4::CreateZRotationMatrix(const float& p_angle)
{
	Mat4 rotZ;

	rotZ.data[2][2] = 1.f;
	rotZ.data[3][3] = 1.f;
	rotZ.data[0][0] = cos(p_angle);
	rotZ.data[0][1] = -sin(p_angle);
	rotZ.data[1][0] = sin(p_angle);
	rotZ.data[1][1] = cos(p_angle);

	return rotZ;
}
