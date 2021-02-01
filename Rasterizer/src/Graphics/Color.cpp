#include  <iostream>

#include "../../includes/Graphics/Color.h"

using namespace Graphics;

Color::Color(const unsigned char& p_r,
             const unsigned char& p_g,
             const unsigned char& p_b,
             const unsigned char& p_a) : r {p_r}, g {p_g}, b {p_b}, a {p_a}
{
	//	std::cout << "Color created" << std::endl;
}

Color::~Color()
{
	//	std::cout << "Color detroyed" << std::endl;
}

Color Color::White() { return Color(255, 255, 255); }
Color Color::Black() { return Color(0, 0, 0); }
Color Color::Red() { return Color(255, 0, 0); }
Color Color::Green() { return Color(0, 255, 0); }
Color Color::Blue() { return Color(0, 0, 255); }
Color Color::Magenta() { return Color(255, 0, 255); }
Color Color::Cyan() { return Color(0, 255, 255); }
Color Color::Yellow() { return Color(255, 255, 0); }
