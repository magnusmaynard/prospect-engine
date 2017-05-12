#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "ShaderProgram.h"
#include <noise/module/perlin.h>

class CubeMap
{
public:
   CubeMap()
   {
      m_shader.Add(VertexShader("cubemap"));
      m_shader.Add(FragmentShader("cubemap"));
      m_shader.Compile();

      m_modelLocation = m_shader.GetUniformLocation("model");
      m_viewLocation = m_shader.GetUniformLocation("view");
      m_projectionLocation = m_shader.GetUniformLocation("projection");

      GenerateCubeMap();
   }

   ~CubeMap()
   {
   }

   void Draw(const glm::mat4& view, const glm::mat4& projection)
   {
      //Bind.
      m_shader.Use();

      //Uniforms.
      glUniformMatrix4fv(m_modelLocation, 1, GL_FALSE, &m_transform[0][0]);
      glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, &view[0][0]);
      glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, &projection[0][0]);

      ////Textures.
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);//Can this be moved out of the render?

      glBindTextureUnit(0, m_texture);

      //Draw.
      glDrawArrays(GL_TRIANGLES, 0, 6);

      //Unbind.
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

private:
   ShaderProgram m_shader;
   GLint m_modelLocation = 0;
   GLint m_viewLocation = 0;
   GLint m_projectionLocation = 0;

   GLuint m_texture;

   glm::mat4 m_transform;

   void GenerateCubeMap()
   {
      glm::vec4 faceColors[6] =
      {
         glm::vec4(1, 0, 0, 1),
         glm::vec4(0, 1, 0, 1),
         glm::vec4(0, 0, 1, 1),
         glm::vec4(1, 1, 0, 1),
         glm::vec4(0, 1, 1, 1),
         glm::vec4(1, 0, 1, 1),
      };

      int size = 1000;
      int faceCount = 6;

      glGenTextures(1, &m_texture);
      glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
      glTexStorage2D(
         GL_TEXTURE_CUBE_MAP,
         1,
         GL_RGBA32F,
         size, size); //GL_RGB32F

      for (int face = 0; face < faceCount; face++)
      {
         std::vector<glm::vec4> data;
         data.resize(size * size);
         int currentIndex = 0;

         for (int y = 0; y < size; y++)
         {
            for (int x = 0; x < size; x++)
            {
               data[currentIndex] = faceColors[face];
               currentIndex++;
            }
         }

         glTexSubImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
            0,
            0, 0,
            size, size,
            GL_RGBA,
            GL_FLOAT,
            &data[0]);
      }

   }

};
