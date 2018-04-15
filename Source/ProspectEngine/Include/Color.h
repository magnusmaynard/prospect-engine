#pragma once

namespace Prospect
{
   struct Color
   {
#pragma region Presets
      static Color White()
      {
         return { 0.8f, 0.8f, 0.8f };
      }

      static Color Gray()
      {
         return { 0.5f, 0.5f, 0.5f };
      }

      static Color Black()
      {
         return { 0.1f, 0.1f, 0.1f };
      }

      static Color Red()
      {
         return { 0.8f, 0.1f, 0.1f };
      }

      static Color Green()
      {
         return { 0.1f, 0.8f, 0.1f };
      }

      static Color Blue()
      {
         return { 0.1f, 0.1f, 0.8f };
      }
#pragma endregion

      Color(const float r, const float g, const float b, const float a = 1.0)
         :
         R(r),
         G(g),
         B(b),
         A(a)
      {
      }

      glm::vec4 ToRGBA() const
      {
         return { R, G, B, A };
      }

      glm::vec3 ToRGB() const
      {
         return { R, G, B };
      }

      float R;
      float G;
      float B;
      float A;
   };
}
