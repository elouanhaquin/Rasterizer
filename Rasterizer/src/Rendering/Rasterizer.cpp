#include <iostream>
#include <algorithm>

#include "../../includes/Graphics/Color.h"
#include "../../includes/Rendering/Rasterizer.h"
#include <optional>
#include <memory>

using namespace Rendering;
using namespace Graphics;

Rasterizer::Rasterizer(const unsigned int& p_width,
                       const unsigned int& p_height) : m_width {p_width}, m_height {p_height},
                                                       m_ZBuffer {new float[m_width * m_height]}
{
	std::cout << "Rasterizer created" << std::endl;
}

Rasterizer::~Rasterizer()
{
	delete[] m_ZBuffer;

	std::cout << "Rasterizer destroyed" << std::endl;
}

void Rasterizer::RenderScene(Scene* p_scene, Texture* p_target, SDLManager* p_SDLManager,
                             const Mat4& p_projectionMatrix, const Mat4& p_inverseCameraMatrix) const
{
	std::vector<Entity>& entities = p_scene->GetEntities();
	std::vector<Light>& lights = p_scene->GetLights();

	//	p_target->Clear(); // TODO Why here ? #instructions

	for (size_t i = 0; i < entities.size(); ++i)
	{
		std::vector<Vertex> vertices = entities[i].GetMesh()->GetVertices();
		std::vector<int> indices = entities[i].GetMesh()->GetIndices();
		const Mat4& transformMatrix = entities[i].GetTransform();

		for (size_t j = 0; j < indices.size(); j += 3)
		{
			// Find Indices
			const size_t& a = indices[j];
			const size_t& b = indices[j + 1];
			const size_t& c = indices[j + 2];
			
			// Vertices
			Vertex v0 = vertices[a];
			Vertex v1 = vertices[b];
			Vertex v2 = vertices[c];

			// Apply tranform for each vertex
			v0 = Transform(v0, p_projectionMatrix, p_inverseCameraMatrix, transformMatrix);
			v1 = Transform(v1, p_projectionMatrix, p_inverseCameraMatrix, transformMatrix);
			v2 = Transform(v2, p_projectionMatrix, p_inverseCameraMatrix, transformMatrix);

			if (p_SDLManager->IsLight())
			{
				if (p_SDLManager->IsPhong())
				{
					// Apply Phong Light for each vertex
					// TODO Review Phong Method (normal's problem)
					v0 = PhongMethod(v0, lights, p_SDLManager->GetView());
					v1 = PhongMethod(v1, lights, p_SDLManager->GetView());
					v2 = PhongMethod(v2, lights, p_SDLManager->GetView());
				}
				else
				{
					// Apply Blinn-Phong Light for each vertex
					v0 = BlinnPhongMethod(v0, lights, p_SDLManager->GetView());
					v1 = BlinnPhongMethod(v1, lights, p_SDLManager->GetView());
					v2 = BlinnPhongMethod(v2, lights, p_SDLManager->GetView());
				}
			}
			
			// Apply Projection for each vertex
			v0 = Projection(v0, m_width, m_height);
			v1 = Projection(v1, m_width, m_height);
			v2 = Projection(v2, m_width, m_height);

			// Draw Normal
			if (p_SDLManager->IsNormal())
				Normal(v0, v1, v2, p_target);

			// Choose between Bresenham or Barycentric method
			if (p_SDLManager->IsWireframe())
				BresenhamMethod(v0, v1, v2, p_target); // TODO Review Wireframe
			else
				BarycentricMethod(v0, v1, v2, p_target);
		}
	}
}

void Rasterizer::BresenhamCoordinates(const Vertex& p_v0, const Vertex& p_v1, Texture* p_target) const
{
	bool changed = false;

	const float& x1 = p_v0.GetPosition().x;
	const float& y1 = p_v0.GetPosition().y;
	const float& x2 = p_v1.GetPosition().x;
	const float& y2 = p_v1.GetPosition().y;

	float x = x1;
	float y = y1;

	//Get estimation of length
	float dx = abs(x2 - x1);
	float dy = abs(y2 - y1);

	//Get direction of line
	float signX = 0;
	if (x2 - x1 > 0) signX = 1.0f;
	if (x2 - x1 < 0) signX = -1.0f;

	float signY = 0;
	if (y2 - y1 > 0) signY = 1.0f;
	if (y2 - y1 < 0) signY = -1.0f;

	if (dy > dx)
	{
		//Swap values
		std::swap(dx, dy);
		changed = true;
	}

	//Calculate starting error value
	float e = dy / dx - 0.5f;

	for (int i = 0; i <= dx; ++i)
	{
		p_target->SetPixelColor(static_cast<int>(x),
		                        static_cast<int>(y),
		                        p_v0.GetColor());

		while (e >= 0)
		{
			if (changed)
				x += signX;
			else
				y += signY;
			e -= 1;
		}

		if (changed)
			y += signY;
		else
			x += signX;

		e += dy / dx;
	}

	//Draw final point
	p_target->SetPixelColor(static_cast<int>(x2),
	                        static_cast<int>(y2),
	                        p_v1.GetColor());
}

void Rasterizer::BresenhamMethod(const Vertex& p_v0, const Vertex& p_v1, const Vertex& p_v2, Texture* p_target) const
{
	BresenhamCoordinates(p_v1, p_v2, p_target);
	//	BresenhamCoordinates(p_v2, p_v0, p_target);	// Not necessary for Cube (Draw the diagonal for each face)
	BresenhamCoordinates(p_v0, p_v1, p_target);
}

void Rasterizer::BarycentricMethod(const Vertex& p_v0, const Vertex& p_v1, const Vertex& p_v2, Texture* p_target) const
{
	const float area = BarycentricCoordinates(p_v0, p_v1, p_v2);

	const int& x0 = static_cast<int>(p_v0.GetPosition().x);
	const int& y0 = static_cast<int>(p_v0.GetPosition().y);
	const int& x1 = static_cast<int>(p_v1.GetPosition().x);
	const int& y1 = static_cast<int>(p_v1.GetPosition().y);
	const int& x2 = static_cast<int>(p_v2.GetPosition().x);
	const int& y2 = static_cast<int>(p_v2.GetPosition().y);

	// Bounding box of triangle
	unsigned int xMin = std::min(std::min(x0, x1), x2);
	unsigned int yMin = std::min(std::min(y0, y1), y2);
	unsigned int xMax = std::max(std::max(x0, x1), x2);
	unsigned int yMax = std::max(std::max(y0, y1), y2);

	// TODO Review Method to Clip
	// Clip the texture
	xMin = (xMin < 0u) ? 0u : xMin;
	yMin = (yMin < 0u) ? 0u : yMin;
	xMax = (xMax > m_width) ? m_width : xMax;
	yMax = (yMax > m_height) ? m_height : yMax;

	// SetColor for pixel in the triangle
	for (unsigned int x = xMin; x <= xMax; ++x)
		for (unsigned int y = yMin; y <= yMax; ++y)
		{
			const Vertex vertex(Vec3(static_cast<float>(x), static_cast<float>(y), 0));

			float w0 = BarycentricCoordinates(p_v1, p_v2, vertex);
			float w1 = BarycentricCoordinates(p_v2, p_v0, vertex);
			float w2 = BarycentricCoordinates(p_v0, p_v1, vertex);

			// Inside Triangle
			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				w0 /= area;
				w1 /= area;
				w2 /= area;

				const float z = 1 / (w0 / p_v0.GetPosition().z + w1 / p_v1.GetPosition().z + w2 / p_v2.GetPosition().z);
				
				// TODO Review Z-Buffer condition (Check with projection matrix)
				// Z-Buffer
				if (z < m_ZBuffer[y * m_width + x])
				{
					p_target->SetPixelColor(x, y, Color(
						                        static_cast<unsigned char>(w0 * p_v0.GetColor().r + w1 * p_v1.GetColor().r + w2 * p_v2.GetColor().r),
						                        static_cast<unsigned char>(w0 * p_v0.GetColor().g + w1 * p_v1.GetColor().g + w2 * p_v2.GetColor().g),
						                        static_cast<unsigned char>(w0 * p_v0.GetColor().b + w1 * p_v1.GetColor().b + w2 * p_v2.GetColor().b),
						                        static_cast<unsigned char>(w0 * p_v0.GetColor().a + w1 * p_v1.GetColor().a + w2 * p_v2.GetColor().a)));

					m_ZBuffer[y * m_width + x] = z;
				}
			}
		}
}

void Rasterizer::Normal(const Vertex& p_v0, const Vertex& p_v1, const Vertex& p_v2, Texture* p_target) const
{
	const Vertex& n0 = Vertex(p_v0.GetNormal() * 50.f + p_v0.GetPosition());
	const Vertex& n1 = Vertex(p_v1.GetNormal() * 50.f + p_v1.GetPosition());
	const Vertex& n2 = Vertex(p_v2.GetNormal() * 50.f + p_v2.GetPosition());
	const Vertex& p0 = Vertex(p_v0.GetPosition());
	const Vertex& p1 = Vertex(p_v1.GetPosition());
	const Vertex& p2 = Vertex(p_v2.GetPosition());

	BresenhamCoordinates(p0, n0, p_target);
	BresenhamCoordinates(p1, n1, p_target);
	BresenhamCoordinates(p2, n2, p_target);
}

void Rasterizer::Clear() const
{
	for (unsigned int i = 0; i < m_width * m_height; ++i)
		m_ZBuffer[i] = FLT_MAX;
}

Vertex Rasterizer::Transform(const Vertex& p_vertex, const Mat4& p_projectionMatrix, const Mat4& p_inverseCameraMatrix,
                             const Mat4& p_transformMatrix)
{
	Vec4 position(p_vertex.GetPosition());
	Vec4 normal(p_vertex.GetNormal());

	position = p_projectionMatrix * p_inverseCameraMatrix * p_transformMatrix * position;
	position.Homogenize();
	normal = p_transformMatrix.GetInverse().GetTranspose() * normal;
	normal.Normalize();

	return Vertex(position.ToVec3(), normal.ToVec3(), p_vertex.GetColor());
}

Vertex Rasterizer::Projection(const Vertex& p_vertex, const unsigned int& p_width, const unsigned int& p_height)
{
	Vec4 position(p_vertex.GetPosition());

	float x = p_vertex.GetPosition().x;
	float y = p_vertex.GetPosition().y;
	const float& z = p_vertex.GetPosition().z;

	const int sizeX = 1;
	const int sizeY = 1;

	x = ((x / sizeX) + 1) * 0.5f * p_width;
	y = p_height - ((y / sizeY) + 1) * 0.5f * p_height;

	return Vertex(Vec3(x, y, z), p_vertex.GetNormal(), p_vertex.GetColor());
}

Vertex Rasterizer::PhongMethod(const Vertex& p_vertex, const std::vector<Light>& p_lights, const Vec3& p_cameraPos)
{
	Color color;

	for (size_t i = 0; i < p_lights.size(); ++i)
	{
		const float shininess = 1.f;
		const Vec3& L = p_lights[i].GetPosition() - p_vertex.GetPosition();
		const Vec3& N = p_vertex.GetNormal();
		const Vec3& R = N * (L * N) * 2.f - L;
		const Vec3& V = p_cameraPos - p_vertex.GetPosition();
		const float ambiant = p_lights[i].GetAmbiantComponent();
		const float diffuse = p_lights[i].GetDiffuseComponent() * (L * N);
		const float specular = p_lights[i].GetSpecularComponent() * powf((R * V), shininess);

		color.r += static_cast<unsigned char>(p_vertex.GetColor().r * (ambiant + diffuse + specular));
		color.g += static_cast<unsigned char>(p_vertex.GetColor().g * (ambiant + diffuse + specular));
		color.b += static_cast<unsigned char>(p_vertex.GetColor().b * (ambiant + diffuse + specular));
		color.a += static_cast<unsigned char>(p_vertex.GetColor().a * (ambiant + diffuse + specular));
	}

	return Vertex(p_vertex.GetPosition(), p_vertex.GetNormal(), color);
}

Vertex Rasterizer::BlinnPhongMethod(const Vertex& p_vertex, const std::vector<Light>& p_lights,
	const Vec3& p_cameraPos)
{
	Color color = Color::White();

	for (size_t i = 0; i < p_lights.size(); ++i)
	{
		// TODO Do Blinn-Phong Method
	}

	return Vertex(p_vertex.GetPosition(), p_vertex.GetNormal(), color);
}

float Rasterizer::BarycentricCoordinates(const Vertex& p_v0, const Vertex& p_v1, const Vertex& p_v2)
{
	return ((p_v2.GetPosition().x - p_v1.GetPosition().x) * (p_v1.GetPosition().y - p_v0.GetPosition().y) -
		(p_v2.GetPosition().y - p_v1.GetPosition().y) * (p_v1.GetPosition().x - p_v0.GetPosition().x));
}

Mat4 Rasterizer::CreatePerspectiveProjectionMatrix(const int& p_width, const int& p_height, const float& p_near,
                                                   const float& p_far, const float& p_fov)
{
	// TODO Review Perspective matrix (inverse y)
	Mat4 projection;

	const float scale = static_cast<float>(1 / (tan((p_fov / 2) * (M_PI / 180))));
	const float ratio = static_cast<float>(p_width / static_cast<float>(p_height));

	projection.data[0][0] = scale;
	projection.data[1][1] = scale * ratio;
	projection.data[2][2] = -p_far / (p_far - p_near);
	projection.data[2][3] = -1.f;
	projection.data[3][2] = -(p_far * p_near) / (p_far - p_near);

	return projection;
}
