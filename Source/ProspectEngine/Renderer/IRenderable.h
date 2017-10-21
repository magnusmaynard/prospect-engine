#pragma once

namespace Prospect
{
   class IRenderable
   {
   public:
      virtual ~IRenderable() {};
      virtual void Render() = 0;
   };
}