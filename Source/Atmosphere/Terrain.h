#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "ShaderProgram.h"

class Terrain
{
public:
   Terrain();
   ~Terrain();
   void Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& sunDirection);
   void Transform(const glm::mat4& transform);
   void GeneratePlane();
private:
   ShaderProgram m_shader;
   GLint m_modelLocation = 0;
   GLint m_viewLocation = 0;
   GLint m_projectionLocation = 0;
   GLint m_sunDirectionLocation = 0;

   GLuint m_VAO;

   enum BUFFERS
   {
      BUFFER_POINT,
      BUFFER_INDEX,
      BUFFER_NORMAL,
      BUFFER_COUNT
   };
   GLuint m_buffers[BUFFER_COUNT];

   glm::mat4 m_transform;

   const glm::vec3 m_origin; //TODO: earthPosition
   const float m_radius;
   const int m_sectionCount;//benchmark=400.

   glm::vec3* m_points;
   unsigned int* m_indices;
   glm::vec3* m_normals;

   int m_pointsSize;
   int m_indicesSize;
   int m_normalsSize;
};
