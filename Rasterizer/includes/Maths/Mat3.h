#pragma once

namespace Maths
{
	class Mat3
	{
	public:
		float data[3][3];

	public:
		Mat3();
		~Mat3();

		float Determinant() const;
	};
}
