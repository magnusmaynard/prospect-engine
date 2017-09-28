#pragma once
#include <map>
#include "Renderables/RenderableEntity.h"
#include "UniformBuffer.h"
#include <memory>
#include "Renderer/VertexData.h"
#include "Renderer/Shaders/ShaderFactory.h"

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
      void Render(Scene_impl& scene);

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
   };
}
