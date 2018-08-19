#include "ProspectEngine_pch.h"

#include "Frustum.h"

using namespace Prospect;
using namespace glm;

Frustum::Frustum(const float nearPlane, const float farPlane, const float fovY, const float aspect)
{
   const float halfFovRadsY = radians(fovY * 0.5f);
   const float halfFovRadsX = atan(aspect * tan(halfFovRadsY));

   const vec3 nearMax = { tan(halfFovRadsX) * nearPlane, tan(halfFovRadsY) * nearPlane, nearPlane };
   Corners[0] = { +nearMax.x, +nearMax.y, -nearMax.z };
   Corners[1] = { -nearMax.x, +nearMax.y, -nearMax.z };
   Corners[2] = { +nearMax.x, -nearMax.y, -nearMax.z };
   Corners[3] = { -nearMax.x, -nearMax.y, -nearMax.z };

   const vec3 farMax = { tan(halfFovRadsX) * farPlane, tan(halfFovRadsY) * farPlane, farPlane };
   Corners[4] = { +farMax.x, +farMax.y, -farMax.z };
   Corners[5] = { -farMax.x, +farMax.y, -farMax.z };
   Corners[6] = { +farMax.x, -farMax.y, -farMax.z };
   Corners[7] = { -farMax.x, -farMax.y, -farMax.z };
}
