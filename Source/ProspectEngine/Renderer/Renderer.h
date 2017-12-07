#pragma once

#include "Renderer/Renderables/RenderableEntity.h"
#include "Renderer/VertexData.h"
#include "Renderer/Shaders/ShaderFactory.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Renderer/Renderables/RenderableTerrain.h"
#include "Renderer/Renderables/RenderableText.h"
#include "Renderer/Renderables/Atmosphere/RenderableAtmosphere.h"
#include "Renderer/Textures/DepthTexture.h"

namespace Prospect
{
   class Scene_impl;
   class Mesh_impl;
   class Material;
   class VertexData;

   class Renderer
   {
   public:
      Renderer();

      void Render(double time, Scene_impl& scene);

      void ShowFPS(bool showFPS);
      void ShowWireframe(bool showWireframe);
      void Resize(const glm::ivec2& size);

   private:
      std::deque<std::unique_ptr<IRenderable>> m_renderables;
      std::unique_ptr<RenderableTerrain> m_terrain;
      std::unique_ptr<RenderableText> m_fpsText;
      std::unique_ptr<RenderableAtmosphere> m_atmosphere;

      std::map<int, VertexData> m_vertexDataMap;
      GlobalUniformBuffers m_globalUniformBuffers;

      bool m_showFPS;
      bool m_showWireframe;
      unsigned int m_frameCount;
      double m_previousTime;

      void Initialize();

      void UpdateRenderableEntity(Entity_impl& entity);
      void UpdateRenderableEntities(const Scene_impl& scene);
      void UpdateGlobalUniformBuffers(const Scene_impl& scene);
      void UpdateRenderableTerrain(const Scene_impl& scene);
      void UpdateRenderableAtmosphere(const Scene_impl& scene);

      VertexData& GetVertexData(Mesh_impl& mesh);

      void UpdateFPS(double time);

      void Clear();
      void ClearDepthBuffer();
      void ReportErrors() const;

      DepthTexture m_depthTexture;
   };
}
