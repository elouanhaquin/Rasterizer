#include <iostream>
#include <cmath>

#include "../../includes/Maths/Vec3.h"

using namespace Maths;

Vec3::Vec3(const float& p_x,
           const float& p_y,
           const float& p_z) : x {p_x}, y {p_y}, z {p_z}
{
	//	std::cout << "Vec3 created" << std::endl;
}

Vec3::~Vec3()
{
	//	std::cout << "Vec3 detroyed" << std::endl;
}

float Vec3::GetMagnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

void Vec3::Normalize()
{
	const float magnitude = GetMagnitude();

	if (magnitude != 0)
	{
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}
}

Vec3 Vec3::operator+(const Vec3& p_vector) const
{
	return Vec3(x + p_vector.x, 
				y + p_vector.y,
				z + p_vector.z);
}

Vec3 Vec3::operator-(const Vec3& p_vector) const
{
	return Vec3(x - p_vector.x,
				y - p_vector.y,
				z - p_vector.z);
}

float Vec3::operator*(const Vec3& p_vector) const
{
	return (x * p_vector.x + y * p_vector.y + z * p_vector.z);
}

Vec3 Vec3::operator*(const float& p_scalar) const
{
	return Vec3(x * p_scalar,
				y * p_scalar,
				z * p_scalar);
}
