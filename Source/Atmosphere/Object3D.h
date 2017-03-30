#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/mat4x2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "ShaderProgram.h"

class Object3D
{
public:
   Object3D()
      :
      m_shader("object3D.vs.glsl", "object3D.fs.glsl")
   {
      //TEMP
      m_points = {
         glm::vec3(-10.0, -0.2, 10.0),
         glm::vec3(10.0, -0.2, 10.0),
         glm::vec3(-10.0, -0.2, -10.0),
         glm::vec3(10.0, -0.2, 10.0),
         glm::vec3(10.0, -0.2, -10.0),
         glm::vec3(-10.0, -0.2, -10.0)
      };

      m_modelLocation = m_shader.GetUniformLocation("model");
      m_viewLocation = m_shader.GetUniformLocation("view");
      m_projectionLocation = m_shader.GetUniformLocation("projection");

      glCreateVertexArrays(1, &m_VAO);
      glBindVertexArray(m_VAO);

      glCreateBuffers(BUFFER_COUNT, m_buffers);

      //Initialize point buffer.
      glNamedBufferStorage(
         m_buffers[BUFFER_POINT],
         m_points.size() * 3 * sizeof(float),
         &m_points[0],
         0);

      //Bind buffer to vertex array.
      glVertexArrayVertexBuffer(m_VAO, 0, m_buffers[BUFFER_POINT], 0, sizeof(glm::vec3));

      //Specify the format of the atrribute.
      glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

      //Specify which vertex buffer binding to use for the attribute.
      glVertexArrayAttribBinding(m_VAO, 0, 0);

      //Enable attribute.
      glEnableVertexArrayAttrib(m_VAO, 0);
   }

   ~Object3D()
   {
      //Dispose.
      glDeleteBuffers(BUFFER_COUNT, m_buffers);
      glDeleteVertexArrays(1, &m_VAO);
   }

   void Draw(const glm::mat4& view, const glm::mat4& projection)
   {
      //Bind
      m_shader.Use();
      glBindVertexArray(m_VAO);
      glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BUFFER_POINT]);

      //Uniforms
      glUniformMatrix4fv(m_modelLocation, 1, GL_FALSE, &m_model[0][0]);
      glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, &view[0][0]);
      glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, &projection[0][0]);

      //Draw
      glDrawArrays(GL_TRIANGLES, 0, m_points.size());

      //Unbind
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

private:
   ShaderProgram m_shader;
   GLint m_modelLocation = 0;
   GLint m_viewLocation = 0;
   GLint m_projectionLocation = 0;

   GLuint m_VAO;

   enum BUFFERS
   {
      BUFFER_POINT,
      //BUFFER_INDEX,
      BUFFER_COUNT
   };
   GLuint m_buffers[BUFFER_COUNT];

   glm::mat4 m_model;
   std::vector<glm::vec3> m_points;
   //std::vector<unsigned int> m_indices;
};
