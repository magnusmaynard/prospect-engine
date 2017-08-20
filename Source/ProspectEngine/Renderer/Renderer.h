#pragma once

namespace Prospect
{
   class Terrain;
   class Scene_impl;

   class Renderer
   {
   public:
      Renderer();

      void Render(Scene_impl& scene);
      void Render(Terrain& terrain);
   };
}
