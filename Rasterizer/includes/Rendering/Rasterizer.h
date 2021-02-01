#pragma once

#include "../World/Scene.h"
#include "../Graphics/Texture.h"

using namespace World;
using namespace Graphics;

namespace Rendering
{
	class Rasterizer
	{
	private:
		unsigned int m_width;
		unsigned int m_height;

		float* m_ZBuffer;

	public:
		explicit Rasterizer(const unsigned int& p_width, const unsigned int& p_height);
		~Rasterizer();

		void RenderScene(Scene* p_scene,
		                 Texture* p_target,
		                 SDLManager* p_SDLManager,
		                 const Mat4& p_projectionMatrix,
		                 const Mat4& p_inverseCameraMatrix) const;
		void BresenhamCoordinates(const Vertex& p_v0,
		                          const Vertex& p_v1,
		                          Texture* p_target) const;
		void BresenhamMethod(const Vertex& p_v0,
		                     const Vertex& p_v1,
		                     const Vertex& p_v2,
		                     Texture* p_target) const;
		void BarycentricMethod(const Vertex& p_v0,
		                       const Vertex& p_v1,
		                       const Vertex& p_v2,
		                       Texture* p_target) const;
		void Normal(const Vertex& p_v0,
					const Vertex& p_v1,
					const Vertex& p_v2,
					Texture* p_target) const;
		void Clear() const;

		static Vertex Transform(const Vertex& p_vertex,
		                        const Mat4& p_projectionMatrix,
		                        const Mat4& p_inverseCameraMatrix,
		                        const Mat4& p_transformMatrix);
		static Vertex Projection(const Vertex& p_vertex,
		                         const unsigned int& p_width,
		                         const unsigned int& p_height);
		static Vertex PhongMethod(const Vertex& p_vertex,
		                          const std::vector<Light>& p_lights,
		                          const Vec3& p_cameraPos);
		static Vertex BlinnPhongMethod(const Vertex& p_vertex,
									   const std::vector<Light>& p_lights,
									   const Vec3& p_cameraPos);

		static float BarycentricCoordinates(const Vertex& p_v0,
		                                    const Vertex& p_v1,
		                                    const Vertex& p_v2);

		static Mat4 CreatePerspectiveProjectionMatrix(const int& p_width,
		                                              const int& p_height,
		                                              const float& p_near,
		                                              const float& p_far,
		                                              const float& p_fov);
	};
}
