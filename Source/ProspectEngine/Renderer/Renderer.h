#pragma once
#include <map>
#include "Renderables/Renderable.h"
#include "Renderables/RenderableMesh.h"
#include "Renderables/RenderableMaterial.h"

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

      void Render(Scene_impl& scene);

   private:
      std::map<int, Renderable> m_renderables;
      std::map<int, RenderableMesh> m_renderableMeshes;
      std::map<int, RenderableMaterial> m_renderableMaterials;

      RenderableMaterial& GetRenderableMaterial(Material& mesh);
      RenderableMesh& GetRenderableMesh(Mesh_impl& mesh);

      void UpdateRenderables(EntityLibrary& entityLib);

      void ApplyCommonUniforms(Scene_impl& scene);

      void Render(Renderable& renderable);

      void Clear();
   };
}
