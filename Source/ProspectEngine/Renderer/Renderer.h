#pragma once

#include "Renderer/Window.h"
#include "Renderer/Renderables/RenderableEntity.h"
#include "Renderer/VertexData.h"
#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Renderer/Renderables/RenderableTerrain.h"
#include "Renderer/Renderables/RenderableText.h"
#include "Renderer/Renderables/RenderableSun.h"
#include "Renderer/Renderables/RenderableAtmosphere.h"
#include "Renderer/Pipeline/GBuffer.h"
#include "Renderer/Pipeline/LightingPass.h"
#include "ShadowMap.h"

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
      std::unique_ptr<RenderableTerrain> m_terrain;
      std::unique_ptr<RenderableText> m_fpsText;
      std::unique_ptr<RenderableAtmosphere> m_atmosphere;
      std::unique_ptr<RenderableSun> m_sun;

      std::map<int, VertexData> m_vertexDataMap;
      GlobalUniformBuffers m_globalUniformBuffers;

      bool m_showFPS;
      bool m_showWireframe;
      unsigned int m_frameCount;
      double m_previousTime;

      ShaderLibrary m_shaderLibrary;
      const MaterialLibrary_impl& m_materialLibrary;

      void Initialize();
      
      void GeometryPass();
      void ShadowPass(Scene_impl& scene);
      void LightingPass2();
      void EffectsPass();

      void UpdateState();

      void UpdateRenderableEntity(Entity_impl& entity);
      void UpdateGlobalUniformBuffers(const Scene_impl& scene);
      void UpdateRenderableTerrain(const Scene_impl& scene);
      void UpdateRenderableAtmosphere(const Scene_impl& scene);
      void UpdateRenderableSun(const Scene_impl& scene);

      VertexData& GetVertexData(Mesh_impl& mesh);

      void UpdateFPS(double time);

      void Clear();
      void ClearDepthBuffer();

      void BindDefaultFramebuffer();


      void UpdateShadowMap(DirectionalLight_impl& light);
      glm::mat4 GetShadowMatrix(const DirectionalLight_impl& light) const;

      std::deque<ShadowMap> m_shadowMaps;
      GBuffer m_gBuffer;
      LightingPass m_lightingPass;
      glm::ivec2 m_size;
   };
}
