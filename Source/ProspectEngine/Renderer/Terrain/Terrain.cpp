#include "ProspectEngine_pch.h"

#include "Terrain.h"
#include <noise/noise.h>
#include "Renderer/Shaders/TessEvaluationShader.h"
#include "Renderer/UniformBuffer.h"

#include "Resources/Resources.h"
#include "Scene/Scene_impl.h"
#include "Include/Camera.h"
#include "Renderer/Shaders/ShaderFactory.h"
#include "Renderer/Shaders/Shader.h"
#include "Resources/ResourceIO.h"

using namespace Prospect;
using namespace noise;
using namespace glm;

Terrain::Terrain()
   :
   m_shader(ShaderFactory::CreateShader(
      Resources::TERRAIN_VERTEX_SHADER,
      Resources::TERRAIN_TESSCONTROL_SHADER,
      Resources::TERRAIN_TESSEVALUATION_SHADER,
      Resources::TERRAIN_FRAGMENT_SHADER)),
   m_terrainMap(ResourceIO::ReadBitmap(Resources::TERRAIN_MAP_BITMAP)),
   m_heightScale(200),
   m_totalSize(1000)
{
   m_heightScaleLocation = m_shader.GetUniformLocation("heightScale");
   m_totalSizeLocation = m_shader.GetUniformLocation("totalSize");

   //TODO: This needs a better solution, uniform blocks?
   QuadTreeUniformLocations quadtreeLocations = QuadTreeUniformLocations(
      m_shader.GetUniformLocation("nodeOrigin"),
      m_shader.GetUniformLocation("nodeSize"),
      m_shader.GetUniformLocation("nodeLevel"),
      m_shader.GetUniformLocation("nodeEdgeScaling"));

   glCreateVertexArrays(1, &m_VAO);
   glBindVertexArray(m_VAO);

   m_quadTree = std::make_unique<QuadTree>(vec3(), m_totalSize, quadtreeLocations);

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
   uniformBuffer.Bind();
   glUniform1f(m_heightScaleLocation, m_heightScale);
   glUniform1f(m_totalSizeLocation, m_totalSize);

   //Textures.
   glBindTextureUnit(0, m_texture);

   //Draw.
   const Camera& camera = scene.GetCamera();

   m_quadTree->Update(camera.GetPosition(), camera.GetForward());
   m_quadTree->Draw();
}

void Terrain::GenerateHeightMap()
{
   glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);
   glTextureStorage2D(m_texture, 4, GL_R32F, m_terrainMap.Width, m_terrainMap.Height);
   glTextureSubImage2D(
      m_texture,
      0,
      0, 0,
      m_terrainMap.Width, m_terrainMap.Height,
      GL_RED,
      GL_FLOAT,
      &m_terrainMap.Data[0]);

   glTextureParameteri(m_texture, GL_TEXTURE_BASE_LEVEL, 0);
   glTextureParameteri(m_texture, GL_TEXTURE_MAX_LEVEL, 4);
   glTextureParameteri(m_texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTextureParameteri(m_texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

   glGenerateTextureMipmap(m_texture);

   glTextureParameteri(m_texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTextureParameteri(m_texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
