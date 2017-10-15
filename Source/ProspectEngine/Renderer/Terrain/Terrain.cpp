#include "ProspectEngine_pch.h"

#include "Terrain.h"
#include <noise/noise.h>
#include "Renderer/Shaders/TessEvaluationShader.h"
#include "Renderer/UniformBuffer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Resources/Resources.h"
#include "Scene/Scene_impl.h"
#include "Include/Camera.h"

using namespace Prospect;
using namespace noise;
using namespace glm;

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

   vec3 left(0, 0, -1);
   vec3 top(0, 1, 0);
   vec3 normal = cross(left, top);
   vec3 origin = normal * m_planetRadius;

   m_quadTree = std::make_unique<QuadTree>(
      origin,
      normal,
      left,
      top,
      m_planetRadius,
      vec3(0,0,0),
      quadtreeLocations);

   GenerateHeightMap();
}

Terrain::~Terrain()
{
   //Dispose.
   glDeleteVertexArrays(1, &m_VAO);
}

void Terrain::Render(const Scene_impl& scene, const UniformBuffer& uniformBuffer)
{
   //Bind.
   m_shader.Bind();

   //Uniforms.
   glUniform1f(m_heightScaleLocation, m_heightScale);
   glUniform1f(m_planetRadiusLocation, m_planetRadius);
   glUniform3fv(m_planetOriginLocation, 1, &m_planetOrigin[0]);

   //Textures.
   glBindTextureUnit(0, m_texture);

   //Draw.
   const Camera& camera = scene.GetCamera();

   m_quadTree->Update(camera.GetPosition(), camera.GetForward());
   m_quadTree->Draw();
}

void Terrain::GenerateHeightMap()
{
   int width = 0;
   int height = 0;
   int channels = 0;
   std::string filePath = Resources::GetTexturePath() + "terrain1.bmp";
   float* data = stbi_loadf(filePath.c_str(), &width, &height, &channels, 1);

   glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);
   glTextureStorage2D(m_texture, 4, GL_R32F, width, height);
   glTextureSubImage2D(
      m_texture,
      0,
      0, 0,
      width, height,
      GL_RED,
      GL_FLOAT,
      data);

   glTextureParameteri(m_texture, GL_TEXTURE_BASE_LEVEL, 0);
   glTextureParameteri(m_texture, GL_TEXTURE_MAX_LEVEL, 4);
   glTextureParameteri(m_texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTextureParameteri(m_texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

   glGenerateTextureMipmap(m_texture);
}
