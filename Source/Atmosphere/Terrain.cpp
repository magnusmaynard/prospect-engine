#pragma once
#include "Terrain.h"
#include <noise/noise.h>
#include "TessControlShader.h"
#include "TessEvaluationShader.h"

using namespace noise;

Terrain::Terrain()
   :
   m_origin(0, 0, 0),
   m_radius(100.0)
{
   m_shader.Add(VertexShader("terrain"));
   m_shader.Add(TessControlShader("terrain"));
   m_shader.Add(TessEvaluationShader("terrain"));
   m_shader.Add(FragmentShader("terrain"));
   m_shader.Compile();

   GeneratePlane();

   m_modelLocation = m_shader.GetUniformLocation("model");
   m_viewLocation = m_shader.GetUniformLocation("view");
   m_projectionLocation = m_shader.GetUniformLocation("projection");
   //m_sunDirectionLocation = m_shader.GetUniformLocation("sunDirection");
   m_originLocation = m_shader.GetUniformLocation("origin");
   m_radiusLocation = m_shader.GetUniformLocation("radius");

   glCreateVertexArrays(1, &m_VAO);
   glBindVertexArray(m_VAO);

   glCreateBuffers(BUFFER_COUNT, m_buffers);

   //Initialize point buffer.
   glNamedBufferStorage(
      m_buffers[BUFFER_POINT], m_points.size() * 3 * sizeof(float), &m_points[0], 0);
   //Bind vertex buffer to vertex array.
   glVertexArrayVertexBuffer(m_VAO, 0, m_buffers[BUFFER_POINT], 0, sizeof(glm::vec3));
   //Specify the format of the atrribute.
   glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
   //Specify which vertex buffer binding to use for the attribute.
   glVertexArrayAttribBinding(m_VAO, 0, 0);
   //Enable attribute.
   glEnableVertexArrayAttrib(m_VAO, 0);

   GenerateHeightTexture();
}

Terrain::~Terrain()
{
   //Dispose.
   glDeleteBuffers(BUFFER_COUNT, m_buffers);
   glDeleteVertexArrays(1, &m_VAO);
}

void Terrain::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& sunDirection)
{
   //Bind.
   m_shader.Use();
   glBindVertexArray(m_VAO);
   glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BUFFER_POINT]);

   //Uniforms.
   glUniformMatrix4fv(m_modelLocation, 1, GL_FALSE, &m_transform[0][0]);
   glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, &view[0][0]);
   glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, &projection[0][0]);
   glUniform1f(m_radiusLocation, m_radius);
   glUniform3fv(m_originLocation, 1, &m_origin[0]);

   //Textures.
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //Can this be moved out of the render?

   glBindTextureUnit(0, m_textures[TEXTURE_HEIGHT]);

   //Draw.
   glPatchParameteri(GL_PATCH_VERTICES, 4);
   glDrawArrays(GL_PATCHES, 0, m_points.size());
   //glDrawArrays(GL_TRIANGLES, 0, m_pointsSize);

   //Unbind.
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Terrain::Transform(const glm::mat4& transform)
{
   m_transform *= transform;
}

void Terrain::GeneratePlane()
{
   static const float FACE_SIZE = m_radius;
   static const float FACE_HALF_SIZE = FACE_SIZE * 0.5;

   m_points = {
      //Front
      glm::vec3(-FACE_HALF_SIZE, -FACE_HALF_SIZE, FACE_HALF_SIZE),
      glm::vec3( FACE_HALF_SIZE, -FACE_HALF_SIZE, FACE_HALF_SIZE),
      glm::vec3(-FACE_HALF_SIZE,  FACE_HALF_SIZE, FACE_HALF_SIZE),
      glm::vec3( FACE_HALF_SIZE,  FACE_HALF_SIZE, FACE_HALF_SIZE),

      //Back
      glm::vec3( FACE_HALF_SIZE, -FACE_HALF_SIZE, -FACE_HALF_SIZE),
      glm::vec3(-FACE_HALF_SIZE, -FACE_HALF_SIZE, -FACE_HALF_SIZE),
      glm::vec3( FACE_HALF_SIZE,  FACE_HALF_SIZE, -FACE_HALF_SIZE),
      glm::vec3(-FACE_HALF_SIZE,  FACE_HALF_SIZE, -FACE_HALF_SIZE),

      //Left
      glm::vec3(-FACE_HALF_SIZE, -FACE_HALF_SIZE, -FACE_HALF_SIZE),
      glm::vec3(-FACE_HALF_SIZE, -FACE_HALF_SIZE,  FACE_HALF_SIZE),
      glm::vec3(-FACE_HALF_SIZE,  FACE_HALF_SIZE, -FACE_HALF_SIZE),
      glm::vec3(-FACE_HALF_SIZE,  FACE_HALF_SIZE,  FACE_HALF_SIZE),

      //Right
      glm::vec3(FACE_HALF_SIZE, -FACE_HALF_SIZE,  FACE_HALF_SIZE),
      glm::vec3(FACE_HALF_SIZE, -FACE_HALF_SIZE, -FACE_HALF_SIZE),
      glm::vec3(FACE_HALF_SIZE,  FACE_HALF_SIZE,  FACE_HALF_SIZE),
      glm::vec3(FACE_HALF_SIZE,  FACE_HALF_SIZE, -FACE_HALF_SIZE),

      //Top
      glm::vec3(-FACE_HALF_SIZE, FACE_HALF_SIZE,  FACE_HALF_SIZE),
      glm::vec3( FACE_HALF_SIZE, FACE_HALF_SIZE,  FACE_HALF_SIZE),
      glm::vec3(-FACE_HALF_SIZE, FACE_HALF_SIZE, -FACE_HALF_SIZE),
      glm::vec3( FACE_HALF_SIZE, FACE_HALF_SIZE, -FACE_HALF_SIZE),

      //Bottom
      glm::vec3(-FACE_HALF_SIZE, -FACE_HALF_SIZE, -FACE_HALF_SIZE),
      glm::vec3( FACE_HALF_SIZE, -FACE_HALF_SIZE, -FACE_HALF_SIZE),
      glm::vec3(-FACE_HALF_SIZE, -FACE_HALF_SIZE,  FACE_HALF_SIZE),
      glm::vec3( FACE_HALF_SIZE, -FACE_HALF_SIZE,  FACE_HALF_SIZE),
   };
}

void Terrain::GenerateHeightTexture()
{
   module::Perlin myModule;
   myModule.SetOctaveCount(6);
   myModule.SetFrequency(4.0);

   int size = 1000; //m_radius
   int currentIndex = 0;
   std::vector<glm::vec4> data;
   data.resize(size * size);

   for (int y = 0; y < size; y++)
   {
      for (int x = 0; x < size; x++)
      {
         float value = static_cast<float>(myModule.GetValue(
            x / static_cast<float>(size),
            y / static_cast<float>(size),
            0)) * 10.0;

         data[currentIndex] = glm::vec4(value, value, value, value);
         currentIndex++;
      }
   }

   glCreateTextures(GL_TEXTURE_2D, 1, &m_textures[TEXTURE_HEIGHT]);

   glTextureStorage2D(m_textures[TEXTURE_HEIGHT], 1, GL_RGB32F, size, size); //TODO: Should this be GL_RGBA32F????

   glTextureSubImage2D(
      m_textures[TEXTURE_HEIGHT],
      0,
      0, 0,
      size, size,
      GL_RGBA,
      GL_FLOAT,
      &data[0]);

   glBindTexture(GL_TEXTURE_2D, m_textures[TEXTURE_HEIGHT]);
}
