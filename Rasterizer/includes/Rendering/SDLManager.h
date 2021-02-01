#pragma once

#include "../../../Dependencies/SDL2/include/SDL.h"
#include "../../../Dependencies/SDL2_ttf/include/SDL_ttf.h"
#include "../Graphics/Color.h"

#include <string>
#include "../Maths/Vec3.h"

using namespace Graphics;
using namespace Maths;

namespace Rendering
{
	class SDLManager
	{
	private:
		SDL_Window* m_window;

		SDL_Renderer* m_renderer;

		TTF_Font* m_font;

		const unsigned int m_windowW;
		const unsigned int m_windowH;

		int m_x_pos;
		int m_y_pos;
		int m_z_pos;
		int m_nb_radius;

		bool m_run;
		bool m_wireframe;
		bool m_light;
		bool m_phong;
		bool m_normal;
		bool m_rotateX;
		bool m_rotateY;
		bool m_rotateZ;

		Vec3 m_pos;
		Vec3 m_dir;
		Vec3 m_view;
		Vec3 m_angle;

		float m_speed;

	public:
		explicit SDLManager(const unsigned int& p_windowW,
		                    const unsigned int& p_windowH);
		~SDLManager();

		bool InitAll();
		bool InitSDL();
		bool InitSDLWindow();
		bool InitSDLRenderer();
		bool InitSDLFont();

		void Setup();
		void Update();
		void Display();
		void Clear(const Color& p_color = Color::Black());
		void CheckInput();
		void DrawPixel(const int& p_x,
		               const int& p_y,
		               const Color& p_color);
		void DrawText(const std::string& p_str,
		              const int& p_x,
		              const int& p_y,
		              const int& p_w,
		              const int& p_h,
		              const Color& p_color = Color::White());

		const SDL_Window* GetWindow() const;
		const SDL_Renderer* GetRenderer() const;

		const unsigned int& GetWindowWidth() const;
		const unsigned int& GetWindowHeight() const;

		const bool& IsRunning() const;
		const bool& IsWireframe() const;
		const bool& IsLight() const;
		const bool& IsPhong() const;
		const bool& IsNormal() const;
		const bool& IsRotateX() const;
		const bool& IsRotateY() const;
		const bool& IsRotateZ() const;

		const Vec3& GetPos() const;
		const Vec3& GetDir() const;
		const Vec3& GetView() const;
	};
}
