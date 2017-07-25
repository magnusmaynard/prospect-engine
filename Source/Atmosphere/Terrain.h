#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "ShaderProgram.h"

#include "QuadTree.h"

namespace Prospect
{
   class Terrain
   {
   public:
      Terrain();
      ~Terrain();
      void Draw();

   private:
      void Terrain::GenerateHeightMap(GLuint texture);

      ShaderProgram m_shader;
      GLint m_viewLocation = 0;
      GLint m_projectionLocation = 0;

      GLint m_sizeLocation = 0;
      GLint m_heightScaleLocation = 0;
      GLint m_planetOriginLocation = 0;
      GLint m_planetRadiusLocation = 0;

      GLuint m_VAO;

      enum TEXTURES
      {
         TEXTURE_HEIGHT_POSX,
         TEXTURE_HEIGHT_NEGX,
         TEXTURE_HEIGHT_POSY,
         TEXTURE_HEIGHT_NEGY,
         TEXTURE_HEIGHT_POSZ,
         TEXTURE_HEIGHT_NEGZ,
         TEXTURE_COUNT
      };
      GLuint m_textures[TEXTURE_COUNT];

      glm::mat4 m_transform;

      const glm::vec3 m_planetOrigin;
      const float m_planetRadius;
      const float m_heightScale = 1;//TODO:

      const int NUMBER_OF_QUADTREES = 6;
      std::vector<QuadTree> m_quadTrees;
   };
}
