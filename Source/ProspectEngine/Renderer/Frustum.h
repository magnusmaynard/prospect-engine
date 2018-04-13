#pragma once

namespace Prospect
{
   struct Frustum
   {
      Frustum(const float near, const float far, const float fovY, const float aspect);

      std::array<glm::vec3, 8> Corners;
   };
}