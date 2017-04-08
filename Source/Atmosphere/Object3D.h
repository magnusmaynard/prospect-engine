#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "ShaderProgram.h"

class Object3D
{
public:
   Object3D(
      const std::vector<glm::vec3>& points,
      const std::vector<unsigned int>& indices,
      const std::vector<glm::vec3>& normals);
   ~Object3D();
   void Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& sunDirection);
   void Transform(const glm::mat4& transform);
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
   std::vector<glm::vec3> m_points;
   std::vector<unsigned int> m_indices;
   std::vector<glm::vec3> m_normals;
};
