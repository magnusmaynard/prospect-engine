#pragma once

#include "Renderer/Renderables/RenderableEntity.h"
#include "Renderer/UniformBuffer.h"
#include "Renderer/VertexData.h"
#include "Renderer/Shaders/ShaderFactory.h"
#include "Renderer/Text/Text.h"
#include "Renderer/Terrain/Terrain.h"

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

      void Setup();
      void Render(double time, Scene_impl& scene);

      void ShowFPS(bool showFPS);

   private:
      std::deque<std::unique_ptr<IRenderable>> m_renderables;
      std::unique_ptr<Terrain> m_terrain;
      std::unique_ptr<Text> m_fpsText;

      std::map<int, VertexData> m_vertexDataMap;
      UniformBuffer m_uniformBuffer;
      bool m_showFPS;
      unsigned int m_frameCount;
      double m_previousTime;

      void UpdateRenderableEntities(EntityLibrary& entityLib);
      void UpdateUniformBuffer(Scene_impl& scene);

      VertexData& GetVertexData(Mesh_impl& mesh);

      void UpdateFPS(double time);

      void Clear();
   };
}
