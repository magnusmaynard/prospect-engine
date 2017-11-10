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

      glm::vec4 ToRGBA() const
      {
         return glm::vec4(R, G, B, A);
      }

      float R;
      float G;
      float B;
      float A;
   };
}
