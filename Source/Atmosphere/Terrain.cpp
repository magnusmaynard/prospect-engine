#pragma once
#include "Terrain.h"
#include <noise/noise.h>
#include "TessControlShader.h"
#include "TessEvaluationShader.h"

using namespace noise;

Terrain::Terrain()
   :
   m_origin(0, 0, 0),
   m_size(400.0)
{
   m_shader.Add(VertexShader("terrain"));
   m_shader.Add(TessControlShader("terrain"));
   m_shader.Add(TessEvaluationShader("terrain"));
   m_shader.Add(FragmentShader("terrain"));
   m_shader.Compile();

   m_modelLocation = m_shader.GetUniformLocation("model");
   m_viewLocation = m_shader.GetUniformLocation("view");
   m_projectionLocation = m_shader.GetUniformLocation("projection");

   m_sizeLocation = m_shader.GetUniformLocation("size");

   //TODO: This needs a better solution for this.
   GLint nodeOriginLocation = m_shader.GetUniformLocation("nodeOrigin");
   GLint nodeSizeLocation = m_shader.GetUniformLocation("nodeSize");
   GLint nodeLodLocation = m_shader.GetUniformLocation("nodeLod");

   m_quadTree = std::make_unique<QuadTree>(
      glm::vec3(0, 0, 0), m_size, 1,
      nodeOriginLocation, nodeSizeLocation, nodeLodLocation);

   glCreateVertexArrays(1, &m_VAO);
   glBindVertexArray(m_VAO);

   GenerateHeightTexture();
}

Terrain::~Terrain()
{
   //Dispose.
   glDeleteVertexArrays(1, &m_VAO);
}

void Terrain::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPosition)
{
   //Bind.
   m_shader.Use();

   //Uniforms.
   glUniformMatrix4fv(m_modelLocation, 1, GL_FALSE, &m_transform[0][0]);
   glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, &view[0][0]);
   glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, &projection[0][0]);
   glUniform1f(m_sizeLocation, m_size);

   //Textures.
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //TODO: Can this be moved out of the render?

   glBindTextureUnit(0, m_textures[TEXTURE_HEIGHT]);

   //Draw.
   m_quadTree->Draw(cameraPosition);
}

void Terrain::Transform(const glm::mat4& transform)
{
   m_transform *= transform;
}

void Terrain::GenerateHeightTexture()
{
   module::Perlin myModule;
   myModule.SetOctaveCount(6);
   myModule.SetFrequency(4.0);

   int currentIndex = 0;
   std::vector<glm::vec4> data;
   data.resize(m_size * m_size);

   for (int y = 0; y < m_size; y++)
   {
      for (int x = 0; x < m_size; x++)
      {
         float value = static_cast<float>(myModule.GetValue(
            x / static_cast<float>(m_size),
            y / static_cast<float>(m_size),
            0)) * 8.0;

         data[currentIndex] = glm::vec4(value, value, value, value);
         currentIndex++;
      }
   }

   glCreateTextures(GL_TEXTURE_2D, 1, &m_textures[TEXTURE_HEIGHT]);

   glTextureStorage2D(m_textures[TEXTURE_HEIGHT], 1, GL_RGB32F, m_size, m_size); //TODO: Should this be GL_RGBA32F????

   glTextureSubImage2D(
      m_textures[TEXTURE_HEIGHT],
      0,
      0, 0,
      m_size, m_size,
      GL_RGBA,
      GL_FLOAT,
      &data[0]);

   glBindTexture(GL_TEXTURE_2D, m_textures[TEXTURE_HEIGHT]);
}
