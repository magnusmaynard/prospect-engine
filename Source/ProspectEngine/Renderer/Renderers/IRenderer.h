#pragma once

#pragma once

namespace Prospect
{
   class IRenderer
   {
   public:
      virtual ~IRenderer() {};

      virtual void Render() = 0;
   };
}