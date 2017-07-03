#pragma once
#include "Terrain.h"
#include <noise/noise.h>
#include "TessControlShader.h"
#include "TessEvaluationShader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace noise;

typedef unsigned char byte;
Terrain::Terrain()
   :
   m_origin(0, 0, 0),
   m_size(100.0)
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
   m_heightScaleLocation = m_shader.GetUniformLocation("heightScale");

   //TODO: This needs a better solution, uniform blocks?
   QuadTreeUniformLocations quadtreeLocations = QuadTreeUniformLocations(
      m_shader.GetUniformLocation("nodeOrigin"),
      m_shader.GetUniformLocation("nodeNormal"),
      m_shader.GetUniformLocation("nodeLeft"),
      m_shader.GetUniformLocation("nodeTop"),
      m_shader.GetUniformLocation("nodeSize"),
      m_shader.GetUniformLocation("nodeLevel"),
      m_shader.GetUniformLocation("nodeEdgeScaling"));

   glCreateVertexArrays(1, &m_VAO);
   glBindVertexArray(m_VAO);


   int halfSize = m_size * 0.5;
   std::vector<glm::vec3> left =
   {
      glm::vec3(0, 0, -1),
      glm::vec3(0, 0, 1),
      glm::vec3(-1, 0, 0),
      glm::vec3(-1, 0, 0),
      glm::vec3(-1, 0, 0),
      glm::vec3(1, 0, 0),
   };

   std::vector<glm::vec3> top =
   {
      glm::vec3(0, 1, 0),
      glm::vec3(0, 1, 0),
      glm::vec3(0, 0, 1),
      glm::vec3(0, 0, -1),
      glm::vec3(0, 1, 0),
      glm::vec3(0, 1, 0), //TODO: incorrect z plane??
   };


   for(int i = 0; i < NUMBER_OF_QUADTREES; i++)
   {
      glm::vec3 normal = glm::cross(left[i], top[i]);
      glm::vec3 origin = normal * m_size * 0.5f;

      m_quadTrees.push_back(QuadTree(
         origin,
         normal,
         left[i],
         top[i],
         m_size,
         quadtreeLocations));

      GenerateHeightMap(m_textures[i]);
   }
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
   glUniform1f(m_heightScaleLocation, m_heightScale);

   for (int i = 0; i < NUMBER_OF_QUADTREES; i++)
   {
      //Textures.
      glBindTextureUnit(i, m_textures[i]);

      //Draw.
      m_quadTrees[i].Update(cameraPosition);
      m_quadTrees[i].Draw();
   }
}

void Terrain::Transform(const glm::mat4& transform)
{
   m_transform *= transform;
}


void Terrain::GenerateHeightMap(GLuint texture)
{
   int width = 0;
   int height = 0;
   int channels = 0;
   float* data = stbi_loadf("terrain1.bmp", &width, &height, &channels, 1);

   glCreateTextures(GL_TEXTURE_2D, 1, &m_textures[TEXTURE_HEIGHT_POSX]);
   glTextureStorage2D(m_textures[TEXTURE_HEIGHT_POSX], 4, GL_R32F, width, height); //4
   glTextureSubImage2D(
      m_textures[TEXTURE_HEIGHT_POSX],
      0,
      0, 0,
      width, height,
      GL_RED,
      GL_FLOAT,
      data);

   glTextureParameteri(m_textures[TEXTURE_HEIGHT_POSX], GL_TEXTURE_BASE_LEVEL, 0);
   glTextureParameteri(m_textures[TEXTURE_HEIGHT_POSX], GL_TEXTURE_MAX_LEVEL, 4);
   glTextureParameteri(m_textures[TEXTURE_HEIGHT_POSX], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTextureParameteri(m_textures[TEXTURE_HEIGHT_POSX], GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

   glGenerateTextureMipmap(m_textures[TEXTURE_HEIGHT_POSX]);
}
