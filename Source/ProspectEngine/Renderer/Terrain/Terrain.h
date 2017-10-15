#pragma once
#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "Renderer/Shaders/Shader.h"

#include "Renderer/Terrain/QuadTree.h"
#include "Renderer/Bitmap.h"

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

      Shader& m_shader;

      GLint m_heightScaleLocation;
      GLint m_totalSizeLocation;

      GLuint m_VAO;
      GLuint m_texture;
      glm::mat4 m_transform;

      Bitmap m_terrainMap;
      const float m_heightScale;
      const float m_totalSize;

      std::unique_ptr<QuadTree> m_quadTree;
   };
}
