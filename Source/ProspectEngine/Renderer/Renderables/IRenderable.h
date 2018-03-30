#pragma once

///TODOL:remove this.
namespace Prospect
{
   class IRenderable
   {
   public:
      virtual ~IRenderable() {};

      virtual void Render() = 0;
      virtual void MakeDirty() = 0;
   };
}