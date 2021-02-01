#include <iostream>

#include "../../includes/Rendering/Window.h"

using namespace Rendering;

Window::Window(const unsigned int& p_width,
               const unsigned int& p_height) : m_width {p_width}, m_height {p_height},
                                               m_SDLManager {m_width, m_height},
                                               m_rasterizer {m_width, m_height},
                                               m_texture {m_width, m_height},
                                               m_near {1.f}, m_far {10.f}, m_fov {90.f},
                                               m_startClock {0.f}, m_time {0.f}, m_deltaTime {0.f}
{
	std::cout << "Window created" << std::endl;
}

Window::~Window()
{
	std::cout << "Window destroyed" << std::endl;
}

void Window::Setup()
{
	m_SDLManager.Setup();

	// Add Entities in Scene
	m_scene.AddEntity(Entity(Mesh::CreateCube(Color::Red()),
	                         Mat4::CreateTranslationMatrix(Vec3(-0.5f, 0.f, 2.f))));
	//m_scene.AddEntity(Entity(Mesh::CreateSphere(16, 16, Color::Blue()),
	                        // Mat4::CreateTranslationMatrix(Vec3(0.5f, 0, 2.f))));
	//	m_scene.AddEntity(Entity(Mesh::CreateTriangle(Vertex(-0.5f, -0.5f, 0.f, Color::Red()),
	//												  Vertex(0.5f, -0.5f, 0.f, Color::Green()),
	//												  Vertex(0.f, 0.5f, 0.f, Color::Blue())),
	//							 Mat4::CreateTranslationMatrix(Vec3(0.f, 0.f, -2.5f))));

	// Add Lights in Scene
	m_scene.AddLight(Light(Vec3(0.f, 0.f, 0.f), 0.2f, 0.4f, 0.4f));
}

void Window::Update()
{
	// Clear
	m_SDLManager.Clear(); // Default color is Black

	m_texture.Clear(); // Default Color is Black

	m_rasterizer.Clear();

	// Update
	m_SDLManager.Update(); // SDL CheckInput

	// Transformation
	static float angleX = 0.f;
	static float angleY = 0.f;
	static float angleZ = 0.f;

	static float x = 0.f;
	static float y = 0.f;
	static float z = 3.f;

	static float s = 1.f;

	if (m_SDLManager.IsRotateX())
		angleX += 2.f;
	if (m_SDLManager.IsRotateY())
		angleY += 2.f;
	if (m_SDLManager.IsRotateZ())
		angleZ += 2.f;

	/*m_scene.GetEntities()[0].SetTransform(Mat4::CreateTransformationMatrix(Vec3(angleX, angleY, angleZ),
	                                                                       Vec3(-x, y, z),
	                                                                       Vec3(s, s, s)));*/
	m_scene.GetEntities()[0].SetTransform(Mat4::CreateTransformationMatrix(Vec3(angleX, angleY, angleZ),
	                                                                       Vec3(x, y, z),
	                                                                       Vec3(s, s, s)));

	// Rasterizer (Magic heppens here)
	m_rasterizer.RenderScene(&m_scene,
	                         &m_texture,
	                         &m_SDLManager,
	                         PerspectiveProjectionMatrix(),
	                         InverseCameraMatrix());
}

void Window::Display()
{
	m_texture.DrawPixels(m_SDLManager);

	m_SDLManager.DrawText(std::to_string(m_deltaTime), 70, 10, 30, 40);

	m_SDLManager.Display(); // SDL RenderPresent
}

void Window::Run()
{
	while (m_SDLManager.IsRunning())
	{
		m_startClock = static_cast<float>(SDL_GetTicks());

		Update();

		Display();

		m_deltaTime = 1000.f / (SDL_GetTicks() - m_startClock);
		m_time += m_deltaTime;
	}
}

Mat4 Window::PerspectiveProjectionMatrix() const
{
	return Rasterizer::CreatePerspectiveProjectionMatrix(m_width, m_height, m_near, m_far, m_fov);
}

Mat4 Window::InverseCameraMatrix() const
{
	 Vec3 newVector = m_SDLManager.GetView();

	// TODO Review Camera Control and Limits for user
	// std::cout << newVector.z << std::endl;

/*	 if (newVector.z <= -2.0f)
		 newVector.z = -m_near - 1.5f;
	 
	*/	
	
	return Mat4::CreateTranslationMatrix(newVector).GetInverse();
}

unsigned Window::GetWidth() const { return m_width; }
unsigned Window::GetHeight() const { return m_height; }
