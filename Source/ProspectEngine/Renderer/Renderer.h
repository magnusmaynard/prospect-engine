#pragma once
#include <map>
#include "Renderables/RenderableEntity.h"
#include "Renderables/RenderableMesh.h"
#include "Renderables/RenderableMaterial.h"
#include "UniformBuffer.h"
#include <memory>

namespace Prospect
{
   class Terrain;
   class Scene_impl;
   class Mesh_impl;
   class Material;

   class Renderer
   {
   public:
      Renderer();

      void Setup();
      void Render(Scene_impl& scene);

   private:
      std::deque<std::unique_ptr<IRenderable>> m_renderables;
      std::map<int, RenderableMesh> m_renderableMeshes;
      UniformBuffer m_uniformBuffer;

      RenderableMesh& GetRenderableMesh(Mesh_impl& mesh);

      void UpdateEntityRenderables(EntityLibrary& entityLib);

      void UpdateUniformBuffer(Scene_impl& scene);

      void Render(RenderableEntity& renderable);

      void Clear();
   };
}
