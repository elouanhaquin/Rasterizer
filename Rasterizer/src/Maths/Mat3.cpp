#include <iostream>

#include "../../includes/Maths/Mat3.h"

using namespace Maths;

Mat3::Mat3()
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			data[i][j] = 0.f;

	//	std::cout << "Mat3 created" << std::endl;
}

Mat3::~Mat3()
{
	//	std::cout << "Mat3 destroyed" << std::endl;
}

float Mat3::Determinant() const
{
	return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
		data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
		data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
}
