#include "ProspectEngine_pch.h"

#include "ShadowCascade.h"

#include "Scene/Camera_impl.h"

using namespace Prospect;
using namespace glm;

ShadowCascade::ShadowCascade(
   const float cascadeIndex,
   const int cascadeCount,
   const bool logarithmic,
   const Camera_impl& camera)
{
   const float distance = camera.GetFar() - camera.GetNear();

   if (logarithmic)
   {
      //Calculates the near and far at logarithmic intervals.
      //[Logb(d) = c] => [b = d ^(1/c)].
      //b = base, d = distance, c = cascade count.
      const float logBase = pow(distance, 1.0 / cascadeCount);

      Near = camera.GetNear() + pow(logBase, cascadeIndex);
      Far = Near + pow(logBase, cascadeIndex + 1);
   }
   else
   {
      //Calculates the near and far at linear intervals.
      const float cascadeLength = distance / cascadeCount;

      Near = camera.GetNear() + cascadeLength * cascadeIndex;
      Far = Near + cascadeLength;
   }
}