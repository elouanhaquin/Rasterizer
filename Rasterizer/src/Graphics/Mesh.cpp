#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

#include "../../includes/Graphics/Mesh.h"

using namespace Graphics;

Mesh::Mesh() : m_vertices {}, m_indices {}
{
	std::cout << "Mesh created" << std::endl;
}

Mesh::~Mesh()
{
	m_vertices.clear();
	m_indices.clear();

	std::cout << "Mesh destroyed" << std::endl;
}

void Mesh::AddTriangleIndices(const int& p_a, const int& p_b, const int& p_c)
{
	m_indices.push_back(p_a);
	m_indices.push_back(p_b);
	m_indices.push_back(p_c);
}

Mesh* Mesh::CreateCube(const Color& p_color)
{
	Mesh* cube = new Mesh;

	cube->m_vertices.reserve(8);
	cube->m_indices.reserve(36);

	// Front
	cube->m_vertices.emplace_back(Vec3(-0.5f, -0.5f, 0.5f), Vec3(-0.5f, 0.5f, 0.5f), p_color);
	cube->m_vertices.emplace_back(Vec3(0.5f, -0.5f, 0.5f), Vec3(0.5f, 0.5f, 0.5f), p_color);
	cube->m_vertices.emplace_back(Vec3(0.5f, 0.5f, 0.5f), Vec3(0.5f, -0.5f, 0.5f), p_color);
	cube->m_vertices.emplace_back(Vec3(-0.5f, 0.5f, 0.5f), Vec3(-0.5f, -0.5f, 0.5f), p_color);
	// Back
	cube->m_vertices.emplace_back(Vec3(-0.5f, -0.5f, -0.5f), Vec3(-0.5f, 0.5f, -0.5f), p_color);
	cube->m_vertices.emplace_back(Vec3(0.5f, -0.5f, -0.5f), Vec3(0.5f, 0.5f, -0.5f), p_color);
	cube->m_vertices.emplace_back(Vec3(0.5f, 0.5f, -0.5f), Vec3(0.5f, -0.5f, -0.5f), p_color);
	cube->m_vertices.emplace_back(Vec3(-0.5f, 0.5f, -0.5f), Vec3(-0.5f, -0.5f, -0.5f), p_color);

	// Front
	cube->AddTriangleIndices(0, 1, 2);
	cube->AddTriangleIndices(2, 3, 0);
	// Top
	cube->AddTriangleIndices(1, 5, 6);
	cube->AddTriangleIndices(6, 2, 1);
	// Back
	cube->AddTriangleIndices(7, 6, 5);
	cube->AddTriangleIndices(5, 4, 7);
	// Bottom
	cube->AddTriangleIndices(4, 0, 3);
	cube->AddTriangleIndices(3, 7, 4);
	// Left
	cube->AddTriangleIndices(4, 5, 1);
	cube->AddTriangleIndices(1, 0, 4);
	// Right
	cube->AddTriangleIndices(3, 2, 6);
	cube->AddTriangleIndices(6, 7, 3);

	return cube;
}

Mesh* Mesh::CreateSphere(const int& p_latitudeCount, const int& p_longitudeCount, const Color& p_color)
{
	Mesh* sphere = new Mesh;

	const float radius = 0.5f;

	for (double latNumber = 0; latNumber <= p_latitudeCount; ++latNumber)
	{
		const double angle1 = latNumber * M_PI / p_latitudeCount;				
		const double sinAngle1 = sin(angle1);
		const double cosAngle = cos(angle1);

		for (double longNumber = 0; longNumber <= p_longitudeCount; ++longNumber)
		{
			const double angle2 = longNumber * 2 * M_PI / p_longitudeCount;
			const double sinAngle2 = sin(angle2);
			const double cosAngle2 = cos(angle2);

			const float vX = radius * static_cast<float>(cosAngle2 * sinAngle1);
			const float vY = radius * static_cast<float>(cosAngle);
			const float vZ = radius * static_cast<float>(sinAngle2 * sinAngle1);

			sphere->m_vertices.emplace_back(Vec3(vX, vY, vZ), Vec3(vX, -vY, vZ), p_color);
		}
	}
	for (int latNumber = 0; latNumber < p_latitudeCount; ++latNumber)
	{
		for (int longNumber = 0; longNumber < p_longitudeCount; ++longNumber)
		{
			const int i1 = (latNumber * (p_longitudeCount + 1)) + longNumber;
			const int i2 = i1 + p_longitudeCount + 1;

			sphere->AddTriangleIndices(i1, i2, i1 + 1);
			sphere->AddTriangleIndices(i2, i2 + 1, i1 + 1);
		}
	}

	return sphere;
}

Mesh* Mesh::CreateTriangle(const Vertex& p_a, const Vertex& p_b, const Vertex& p_c)
{
	Mesh* triangle = new Mesh;

	triangle->m_vertices.reserve(3);
	triangle->m_indices.reserve(3);

	triangle->m_vertices.push_back(p_a);
	triangle->m_vertices.push_back(p_b);
	triangle->m_vertices.push_back(p_c);

	triangle->AddTriangleIndices(0, 1, 2);

	return triangle;
}

const std::vector<Vertex>& Mesh::GetVertices() const
{
	return m_vertices;
}

const std::vector<int>& Mesh::GetIndices() const
{
	return m_indices;
}
