#pragma once

namespace Prospect
{
   class UniformBuffer;

   class IRenderable
   {
   public:
      virtual ~IRenderable() {};
      virtual void Render(UniformBuffer& uniformBuffer) = 0;
   };
}