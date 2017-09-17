#pragma once

namespace Prospect
{
   struct Color
   {
      Color(float r, float g, float b, float a = 1.0)
         :
         R(r),
         G(g),
         B(b),
         A(a)
      {
      }

      float R;
      float G;
      float B;
      float A;
   };
}
