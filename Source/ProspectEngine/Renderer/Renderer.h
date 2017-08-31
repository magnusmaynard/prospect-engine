#pragma once
#include <map>
#include "RenderableEntity.h"

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
      std::map<int, RenderableEntity> m_renderables;

      RenderableEntity& GetRenderable(Entity_impl& entity);

      RenderableEntity ConstructRenderable(Entity_impl& entity);

      void Renderer::Render(RenderableEntity& renderable);
   };
}
