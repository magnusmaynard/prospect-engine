#pragma once
#include "Defines.h"
#include <memory>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Prospect
{
   class Camera_impl;

   class Camera
   {
   public:
      Camera(const glm::ivec2& size);
      EXPORT_DLL ~Camera();

      EXPORT_DLL void LookAt(const glm::vec3 eyePosition, const glm::vec3 targetPosition);
      EXPORT_DLL void Resize(const glm::ivec2& size);

      Camera_impl& GetImpl();

   private:
      std::unique_ptr<Camera_impl> m_impl;

   };
}
