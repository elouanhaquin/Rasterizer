#include <iostream>

#include "../../includes//Rendering/SDLManager.h"

using namespace Rendering;

SDLManager::SDLManager(const unsigned& p_windowW,
					   const unsigned& p_windowH) : m_window{ nullptr },
													m_renderer{ nullptr },
													m_font{ nullptr },
													m_windowW{ p_windowW },
													m_windowH{ p_windowH },
													m_x_pos{ 6 },
													m_y_pos{ 6 },
													m_z_pos{ 6 },
													m_nb_radius{ 25 },
													m_run {false},
                                                    m_wireframe {false},
													m_light {false},
													m_phong {false},
                                                    m_normal {false},
                                                    m_pos {0.0f, 0.0f, 0.0f},
                                                    m_dir {0.f, 0.f, 0.f},
                                                    m_view {0.f, 0.f, 0.f},
                                                    m_angle {0.f, 0.f, 0.f},
                                                    m_speed {0.5f}
{
	std::cout << "SDLManager created" << std::endl;
}

SDLManager::~SDLManager()
{
	if (m_font != nullptr)
		TTF_CloseFont(m_font);
	TTF_Quit();
	if (m_renderer != nullptr)
		SDL_DestroyRenderer(m_renderer);
	if (m_window != nullptr)
		SDL_DestroyWindow(m_window);
	SDL_Quit();
	std::cout << "SDLManager detroyed" << std::endl;
}

bool SDLManager::InitAll() { return (InitSDL() && InitSDLWindow() && InitSDLFont()); }

bool SDLManager::InitSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool SDLManager::InitSDLWindow()
{
	m_window = SDL_CreateWindow("Rasterizer",
	                            SDL_WINDOWPOS_CENTERED,
	                            SDL_WINDOWPOS_CENTERED,
	                            m_windowW,
	                            m_windowH, 0);

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Can't initialize SDL !" << std::endl;
		return false;
	}
	if (m_window == nullptr)
	{
		std::cout << "Unable to initialize window: " << SDL_GetError() << std::endl;
		return false;
	}
	return InitSDLRenderer();
}

bool SDLManager::InitSDLRenderer()
{
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (m_renderer == nullptr)
	{
		std::cout << "Unable to initialize renderer: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	return true;
}

bool SDLManager::InitSDLFont()
{
	if (TTF_Init() == -1)
	{
		std::cout << "Unable to initialize TTF: " << SDL_GetError() << std::endl;
		return false;
	}

	m_font = TTF_OpenFont("res/font/rasterizer.ttf", 65);

	if (m_font == nullptr)
	{
		std::cout << "Unable to initialize font: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void SDLManager::Setup()
{
	if (InitAll())
		m_run = true;
}

void SDLManager::Update()
{
	CheckInput();

	SDL_PumpEvents();
}

void SDLManager::Display()
{
	SDL_RenderPresent(m_renderer);
}

void SDLManager::Clear(const Color& p_color)
{
	SDL_SetRenderDrawColor(m_renderer,
	                       p_color.r,
	                       p_color.g,
	                       p_color.b,
	                       p_color.a);
	SDL_RenderClear(m_renderer);
}

void SDLManager::CheckInput()
{
	SDL_Event event;

	const float offset = 0.1f;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			m_run = false;
			break;
		}
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_run = false;
				break;
			case SDLK_n:
				m_normal = !m_normal;
				break;
			case SDLK_l:
				m_light = !m_light;
				if (m_light)
					m_phong = !m_phong;
				break;
			case SDLK_x:
				m_rotateX = !m_rotateX;
				break;
			case SDLK_y:
				m_rotateY = !m_rotateY;
				break;
			case SDLK_z:
				m_rotateZ = !m_rotateZ;
				break;
			case SDLK_F1:
				m_wireframe = !m_wireframe;
				break;
			case SDLK_w:
				m_pos.y += m_dir.y * m_speed;
				break;
			case SDLK_s:
				m_pos.y -= m_dir.y * m_speed;
				break;
			case SDLK_LEFT:
				m_x_pos--;
				m_rotateY = 10;
				m_pos.x = cos(M_PI * m_x_pos / m_nb_radius) * 2;
				m_pos.z = sin(M_PI * m_x_pos / m_nb_radius) * 2;
				break;
			case SDLK_RIGHT:
				m_x_pos++;
				m_pos.x = cos(M_PI * m_x_pos / m_nb_radius) * 2;
				m_pos.z = sin(M_PI * m_x_pos / m_nb_radius) * 2;
				break;
			case SDLK_UP:
				m_y_pos--;
				m_pos.y = cos(M_PI * m_y_pos / m_nb_radius) * 2;
				m_pos.z = sin(M_PI * m_y_pos / m_nb_radius) * 2;			
				break;
			case SDLK_DOWN:
				m_y_pos++;
				m_pos.y = cos(M_PI * m_y_pos / m_nb_radius) * 2;
				m_pos.z = sin(M_PI * m_y_pos / m_nb_radius) * 2;		
				break;
			default:
				break;
			}
		}
				
	//	std::cout << m_dir.x << std::endl;							//IS SEGFAULT APPEND HERE ??
	//	std::cout << m_dir.y << std::endl;							
	//	std::cout << m_dir.z << std::endl;

		m_view = m_pos + m_dir;
	}
}

void SDLManager::DrawPixel(const int& p_x,
                           const int& p_y,
                           const Color& p_color)
{
	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND); // Active Alpha
	SDL_SetRenderDrawColor(m_renderer, p_color.r, p_color.g, p_color.b, p_color.a);
	SDL_RenderDrawPoint(m_renderer, p_x, p_y);
}

void SDLManager::DrawText(const std::string& p_str, const int& p_x, const int& p_y, const int& p_w, const int& p_h,
                          const Color& p_color)
{
	const SDL_Color color = {p_color.r, p_color.g, p_color.b, p_color.a};

	SDL_Surface* surface = TTF_RenderUTF8_Solid(m_font, p_str.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

	int surfaceW, surfaceH;
	SDL_QueryTexture(texture, nullptr, nullptr, &surfaceW, &surfaceH);

	SDL_Rect rect = {p_x - surfaceH, p_y, surfaceW - p_w, surfaceH - p_h};

	SDL_RenderCopy(m_renderer, texture, nullptr, &rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

const SDL_Window* SDLManager::GetWindow() const { return m_window; }
const SDL_Renderer* SDLManager::GetRenderer() const { return m_renderer; }

const unsigned& SDLManager::GetWindowWidth() const { return m_windowW; }
const unsigned& SDLManager::GetWindowHeight() const { return m_windowH; }

const bool& SDLManager::IsRunning() const { return m_run; }
const bool& SDLManager::IsWireframe() const { return m_wireframe; }
const bool& SDLManager::IsLight() const { return m_light; }
const bool& SDLManager::IsPhong() const { return m_phong; }
const bool& SDLManager::IsNormal() const { return m_normal; }
const bool& SDLManager::IsRotateX() const { return m_rotateX; }
const bool& SDLManager::IsRotateY() const { return m_rotateY; }
const bool& SDLManager::IsRotateZ() const { return m_rotateZ; }

const Vec3& SDLManager::GetPos() const { return m_pos; }
const Vec3& SDLManager::GetDir() const { return m_dir; }
const Vec3& SDLManager::GetView() const { return m_view; }
