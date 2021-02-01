#pragma once

namespace Graphics
{
	class Color
	{
	public:
		unsigned char r; //[0, 255]
		unsigned char g; //[0, 255]
		unsigned char b; //[0, 255]
		unsigned char a; //[0, 255]

	public:
		explicit Color(const unsigned char& p_r = 0,
		               const unsigned char& p_g = 0,
		               const unsigned char& p_b = 0,
		               const unsigned char& p_a = 255);
		~Color();

		static Color White();
		static Color Black();
		static Color Red();
		static Color Green();
		static Color Blue();
		static Color Magenta();
		static Color Cyan();
		static Color Yellow();
	};
}
