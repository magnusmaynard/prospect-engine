#pragma once
#include <map>
#include "Renderables/RenderableEntity.h"
#include "UniformBuffer.h"
#include <memory>
#include "Renderer/VertexData.h"
#include "Renderer/Shaders/ShaderFactory.h"
#include "Text/Text.h"

namespace Prospect
{
   class Terrain;
   class Scene_impl;
   class Mesh_impl;
   class Material;
   class VertexData;

   class Renderer
   {
   public:
      Renderer();

      void Setup();
      void Render(double time, Scene_impl& scene);

      void ShowFPS(bool showFPS);

   private:
      std::deque<std::unique_ptr<IRenderable>> m_renderables;
      std::map<int, VertexData> m_vertexDataMap;
      UniformBuffer m_uniformBuffer;

      VertexData& GetVertexData(Mesh_impl& mesh);
      ShaderFactory m_shaderFactory;

      void UpdateRenderableEntities(EntityLibrary& entityLib);

      void UpdateUniformBuffer(Scene_impl& scene);

      void Render(RenderableEntity& renderable);

      void Clear();

      void RenderFPS(double time, const Scene_impl& scene);

      std::unique_ptr<Text> m_fpsText;
      bool m_showFPS;
      unsigned int m_frameCount;
      double m_previousTime;
   };
}
