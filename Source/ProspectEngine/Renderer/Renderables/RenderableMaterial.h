#pragma once
#include "RendererDefines.h"

#include "Include/Material.h"

namespace Prospect
{
   class RenderableMaterial
   {
   public:
      RenderableMaterial(Material& mesh);
      ~RenderableMaterial();
      RenderableMaterial(const RenderableMaterial& other) = delete;
      RenderableMaterial& operator=(const RenderableMaterial &) = delete;
      RenderableMaterial(RenderableMaterial&& other);
      RenderableMaterial& operator=(RenderableMaterial&& other) = delete;

      void Bind();

   private:

      Material& m_material;
   };
}
