#pragma once
#include <map>
#include "Renderable.h"
#include "RenderableMesh.h"

namespace Prospect
{
   class Terrain;
   class Scene_impl;
   class Mesh;

   class Renderer
   {
   public:
      Renderer();

      void Render(Scene_impl& scene);

   private:
      std::map<int, Renderable> m_renderables;
      std::map<int, RenderableMesh> m_renderableMeshes;

      Renderable& GetRenderable(Entity_impl& entity);
      RenderableMesh& GetRenderableMesh(Mesh& mesh);

      void ApplyCommonUniforms(Scene_impl& scene);

      void Render(Renderable& renderable);

      void Clear();
   };
}
