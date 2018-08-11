#pragma once

#include "Renderer/Window.h"
#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Renderer/Pipeline/Framebuffers/GBuffer.h"
#include "Renderer/Pipeline/FrameBuffers/DisplayBuffer.h"
#include "Renderer/Pipeline/FrameBuffers/EffectsBuffer.h"
#include "Renderer/Shadows/ShadowMaps.h"
#include "Renderer/Renderers/EntityRenderer.h"
#include "Renderer/Renderers/TerrainRenderer.h"
#include "Renderer/Renderers/AtmosphereRenderer.h"
#include "Renderer/Renderers/SunRenderer.h"
#include "Renderer/Renderers/TextRenderer.h"
#include "Renderer/Renderers/LightingRenderer.h"
#include "Renderer/Renderers/GodRaysRenderer.h"

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
      Renderer(MaterialLibrary_impl& materialLibrary, const glm::ivec2& size);

      void Render(double time, Scene_impl& scene, Scene2D_impl& scene2D);
      void ShowWireframe(bool showWireframe);
      void Resize(const glm::ivec2& size);

   private:
      GlobalUniformBuffers m_globalUniformBuffers;

      ShaderLibrary m_shaderLibrary;
      MaterialLibrary_impl& m_materialLibrary;

      EntityRenderer m_entityRenderer;
      TerrainRenderer m_terrainRenderer;
      SunRenderer m_sunRenderer;
      TextRenderer m_textRenderer;
      LightingRenderer m_lightingRenderer;
      AtmosphereRenderer m_atmosphereRenderer;
      GodRaysRenderer m_godRaysRenderer;

      void Initialise();
      
      void GeometryPass(Scene_impl& scene);
      void ShadowPass(Scene_impl& scene);
      void LightingPass(Scene_impl& scene);
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
      DisplayBuffer m_displayBuffer;
      EffectsBuffer m_effectsBuffer;
      glm::ivec2 m_size;

      const GLuint DEFAULT_FRAMEBUFFER = 0;
   };
}
