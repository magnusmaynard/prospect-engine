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
   m_planetOrigin(0, 0, 0),
   m_planetRadius(100.0)
{
   m_shader.AddVertexShader("terrain");
   m_shader.AddTessControlShader("terrain");
   m_shader.AddTessEvaluationShader("terrain");
   m_shader.AddFragmentShader("terrain");
   m_shader.Compile();

   m_viewLocation = m_shader.GetUniformLocation("view");
   m_projectionLocation = m_shader.GetUniformLocation("projection");

   m_planetRadiusLocation = m_shader.GetUniformLocation("planetRadius");
   m_planetOriginLocation = m_shader.GetUniformLocation("planetOrigin");
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
      glm::vec3(0, 1, 0),
   };

   for(int i = 0; i < NUMBER_OF_QUADTREES; i++)
   {
      glm::vec3 normal = glm::cross(left[i], top[i]);
      glm::vec3 origin = normal * m_planetRadius;

      m_quadTrees.push_back(QuadTree(
         origin,
         normal,
         left[i],
         top[i],
         m_planetRadius,
         glm::vec3(0,0,0),
         quadtreeLocations));

      GenerateHeightMap(m_textures[i]);
   }
}

Terrain::~Terrain()
{
   //Dispose.
   glDeleteVertexArrays(1, &m_VAO);
}

void Terrain::Draw()
{
   //TODO: get from scene
   const glm::vec3 cameraPosition(0,0,-10);
   const glm::vec3 cameraDirection(0,0,1);

   //Bind.
   m_shader.Use();

   //Uniforms.
   glUniform1f(m_heightScaleLocation, m_heightScale);
   glUniform1f(m_planetRadiusLocation, m_planetRadius);
   glUniform3fv(m_planetOriginLocation, 1, &m_planetOrigin[0]);

   for (int i = 0; i < NUMBER_OF_QUADTREES; i++)
   {
      //Textures.
      glBindTextureUnit(i, m_textures[i]);

      //Draw.
      m_quadTrees[i].Update(cameraPosition, cameraDirection);
      m_quadTrees[i].Draw();
   }
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
