#include <iostream>

#include "../../includes/Graphics/Texture.h"

using namespace Graphics;

Texture::Texture(const unsigned int& p_width,
                 const unsigned int& p_height) : m_width {p_width}, m_height {p_height},
                                                 m_pixel {new Color[m_width * m_height]}
{
	std::cout << "Texture created" << std::endl;
}

Texture::~Texture()
{
	delete[] m_pixel;

	std::cout << "Texture detroyed" << std::endl;
}

void Texture::SetPixelColor(const unsigned int& p_x,
                            const unsigned int& p_y,
                            const Color& p_color)
{
	if (p_x > m_width || p_y > m_height)
		return;
	m_pixel[p_y * m_width + p_x] = p_color;
}

void Texture::DrawPixels(SDLManager& p_SDLManager)
{
	for (unsigned int i = 0; i < m_width * m_height; ++i)
	{
		// Works if SDL Clear is applied
		if ((m_pixel[i].r == 0 && m_pixel[i].g == 0 && m_pixel[i].b == 0) || m_pixel[i].a == 0)
			continue;

		p_SDLManager.DrawPixel(i % m_width, i / m_width, m_pixel[i]);
	}
}

void Texture::Clear(const Color& p_color)
{
	// Memory set if it's the same value of RGBA
	if (p_color.r == p_color.g == p_color.b == p_color.a)
		memset(m_pixel, p_color.r, m_width * m_height);
	else
		for (unsigned int i = 0; i < m_width * m_height; ++i)
			m_pixel[i] = p_color;
}

const unsigned int& Texture::GetWidth() const { return m_width; }
const unsigned int& Texture::GetHeight() const { return m_height; }

const Color* Texture::GetPixel() const { return m_pixel; }
