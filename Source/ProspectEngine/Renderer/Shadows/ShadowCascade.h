#pragma once

namespace Prospect
{
   class Camera_impl;

   struct ShadowCascade
   {
      ShadowCascade(
         const float cascadeIndex,
         const int cascadeCount,
         const bool logarithmic,
         const Camera_impl& camera);

      float Near;
      float Far;
   };
}