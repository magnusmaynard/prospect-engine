#pragma once
#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "Renderer/Shaders/Shader.h"

#include "Renderer/Terrain/QuadTree.h"

namespace Prospect
{
   class Scene_impl;
   class UniformBuffer;

   class Terrain
   {
   public:
      Terrain();
      ~Terrain();
      void Render(const Scene_impl& scene, const UniformBuffer& uniformBuffer);

   private:
      void GenerateHeightMap();

      Shader m_shader;
      GLint m_viewLocation = 0;
      GLint m_projectionLocation = 0;

      GLint m_sizeLocation = 0;
      GLint m_heightScaleLocation = 0;
      GLint m_planetOriginLocation = 0;
      GLint m_planetRadiusLocation = 0;

      GLuint m_VAO;

      GLuint m_texture;

      glm::mat4 m_transform;

      const glm::vec3 m_planetOrigin;
      const float m_planetRadius;
      const float m_heightScale = 1;

      std::unique_ptr<QuadTree> m_quadTree;
   };
}
