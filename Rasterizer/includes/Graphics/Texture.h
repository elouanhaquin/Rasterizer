#pragma once

#include "Color.h"
#include "../Rendering/SDLManager.h"

using namespace Rendering;

namespace Graphics
{
	class Texture
	{
	private:
		unsigned int m_width;
		unsigned int m_height;

		Color* m_pixel;

	public:
		explicit Texture(const unsigned int& p_width,
		                 const unsigned int& p_height);
		~Texture();

		void SetPixelColor(const unsigned int& p_x,
		                   const unsigned int& p_y,
		                   const Color& p_color);
		void DrawPixels(SDLManager& p_SDLManager);

		void Clear(const Color& p_color = Color::Black());

		const unsigned int& GetWidth() const;
		const unsigned int& GetHeight() const;

		const Color* GetPixel() const;
	};
}
