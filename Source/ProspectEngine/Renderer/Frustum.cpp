#include "ProspectEngine_pch.h"

#include "Frustum.h"

using namespace Prospect;
using namespace glm;

Frustum::Frustum(const float near, const float far, const float fovY, const float aspect)
{
   const float halfFovRadsY = radians(fovY * 0.5f);
   const float halfFovRadsX = atan(aspect * tan(halfFovRadsY));

   const vec3 nearMax = { tan(halfFovRadsX) * near, tan(halfFovRadsY) * near, near };
   Corners[0] = { +nearMax.x, +nearMax.y, -nearMax.z };
   Corners[1] = { -nearMax.x, +nearMax.y, -nearMax.z };
   Corners[2] = { +nearMax.x, -nearMax.y, -nearMax.z };
   Corners[3] = { -nearMax.x, -nearMax.y, -nearMax.z };

   const vec3 farMax = { tan(halfFovRadsX) * far, tan(halfFovRadsY) * far, far };
   Corners[4] = { +farMax.x, +farMax.y, -farMax.z };
   Corners[5] = { -farMax.x, +farMax.y, -farMax.z };
   Corners[6] = { +farMax.x, -farMax.y, -farMax.z };
   Corners[7] = { -farMax.x, -farMax.y, -farMax.z };
}
