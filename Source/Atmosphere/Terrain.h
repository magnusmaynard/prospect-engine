#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "ShaderProgram.h"

#include "QuadTree.h"

class Terrain
{
public:
   Terrain();
   ~Terrain();
   void Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPosition);
   void Transform(const glm::mat4& transform);

private:
   void GeneratePlane();
   void GenerateHeightTexture();

   void Update(const glm::vec3& cameraPosition);

   ShaderProgram m_shader;
   GLint m_modelLocation = 0;
   GLint m_viewLocation = 0;
   GLint m_projectionLocation = 0;

   GLint m_originLocation = 0;
   GLint m_sizeLocation = 0;
   GLint m_nodeSizeLocation = 0;
   GLint m_nodeLodLocation = 0;

   GLuint m_VAO;

   enum TEXTURES
   {
      TEXTURE_HEIGHT,
      TEXTURE_COUNT
   };
   GLuint m_textures[TEXTURE_COUNT];

   glm::mat4 m_transform;

   const glm::vec3 m_origin;
   const float m_size;

   QuadTree m_quadTree;
};
