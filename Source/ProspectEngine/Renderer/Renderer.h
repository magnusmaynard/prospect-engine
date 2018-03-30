#pragma once

#include "Renderer/Window.h"
#include "Renderer/Renderables/RenderableEntity.h"
#include "Renderer/VertexData.h"
#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Renderer/Renderables/RenderableText.h"
#include "Renderer/Pipeline/GBuffer.h"
#include "Renderer/Pipeline/LightingPass.h"
#include "Renderer/ShadowMaps.h"
#include "Renderer/Renderers/TerrainRenderer.h"
#include "Renderer/Renderers/AtmosphereRenderer.h"
#include "Renderer/Renderers/SunRenderer.h"

namespace Prospect
{
   class Scene_impl;
   class Mesh_impl;
   class Material;
   class VertexData;

   class Renderer
   {
   public:
      Renderer(const MaterialLibrary_impl& materialLibrary, const glm::ivec2& size);

      void Render(double time, Scene_impl& scene);

      void ShowFPS(bool showFPS);
      void ShowWireframe(bool showWireframe);
      void Resize(const glm::ivec2& size);

   private:
      std::deque<std::unique_ptr<IRenderable>> m_renderables;
      std::unique_ptr<RenderableText> m_fpsText;

      std::map<int, VertexData> m_vertexDataMap;
      GlobalUniformBuffers m_globalUniformBuffers;

      bool m_showFPS;
      bool m_showWireframe;
      unsigned int m_frameCount;
      double m_previousTime;

      ShaderLibrary m_shaderLibrary;
      const MaterialLibrary_impl& m_materialLibrary;

      TerrainRenderer m_terrainRenderer;
      AtmosphereRenderer m_atmosphereRenderer;
      SunRenderer m_sunRenderer;

      void Initialize();
      
      void GeometryPass(Scene_impl& scene);
      void ShadowPass(Scene_impl& scene);
      void LightingPass2();
      void EffectsPass(Scene_impl& scene);

      void UpdateState();

      void UpdateRenderableEntity(Entity_impl& entity);
      void UpdateGlobalUniformBuffers(const Scene_impl& scene);

      VertexData& GetVertexData(Mesh_impl& mesh);

      void UpdateFPS(double time);

      void Clear();
      void ClearDepthBuffer();

      void BindDefaultFramebuffer();

      ShadowMaps m_shadowMaps;
      GBuffer m_gBuffer;
      LightingPass m_lightingPass;
      glm::ivec2 m_size;
   };
}
