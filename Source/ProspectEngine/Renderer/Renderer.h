#pragma once
#include <map>
#include "Renderable.h"

namespace Prospect
{
   class Terrain;
   class Scene_impl;

   class Renderer
   {
   public:
      Renderer();

      void Render(Scene_impl& scene);

   private:
      std::map<int, Renderable> m_renderables;

      Renderable& GetRenderable(Entity_impl& entity);

      void ApplyCommonUniforms(Scene_impl& scene);

      void Render(Renderable& renderable);
   };
}
