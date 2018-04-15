#pragma once

#include "Renderer/Window.h"
#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Renderer/Pipeline/GBuffer.h"
#include "Renderer/Shadows/ShadowMaps.h"
#include "Renderer/Renderers/EntityRenderer.h"
#include "Renderer/Renderers/TerrainRenderer.h"
#include "Renderer/Renderers/AtmosphereRenderer.h"
#include "Renderer/Renderers/SunRenderer.h"
#include "Renderer/Renderers/TextRenderer.h"
#include "Renderer/Renderers/LightingRenderer.h"

namespace Prospect
{
   class Scene2D_impl;
   class Scene_impl;
   class Mesh_impl;
   class Material;
   class VertexData;

   class Renderer
   {
   public:
      Renderer(const MaterialLibrary_impl& materialLibrary, const glm::ivec2& size);

      void Render(double time, Scene_impl& scene, Scene2D_impl& scene2D);
      void ShowWireframe(bool showWireframe);
      void Resize(const glm::ivec2& size);
      const Image Screenshot(Scene_impl& scene);

   private:
      GlobalUniformBuffers m_globalUniformBuffers;

      ShaderLibrary m_shaderLibrary;
      const MaterialLibrary_impl& m_materialLibrary;

      EntityRenderer m_entityRenderer;
      TerrainRenderer m_terrainRenderer;
      AtmosphereRenderer m_atmosphereRenderer;
      SunRenderer m_sunRenderer;
      TextRenderer m_textRenderer;
      LightingRenderer m_lightingRenderer;

      void Initialise();
      
      void GeometryPass(Scene_impl& scene);
      void ShadowPass(Scene_impl& scene);
      void LightingPass();
      void EffectsPass(Scene_impl& scene, Scene2D_impl& scene2D);

      void RenderEntities(Entity_impl& entity);

      void UpdateState();
      void UpdateGlobalUniformBuffers(const Scene_impl& scene);

      void Clear();
      void ClearDepthBuffer();
      void BindDefaultFramebuffer();

      bool m_showWireframe;

      ShadowMaps m_shadowMaps;
      GBuffer m_gBuffer;
      glm::ivec2 m_size;

      GLuint m_screenshotFBO;

   };
}
