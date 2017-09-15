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
      EXPORT_DLL ~Camera();

      EXPORT_DLL void LookAt(const glm::vec3 eyePosition, const glm::vec3 targetPosition);

      EXPORT_DLL void SetSize(const glm::ivec2& size);

      EXPORT_DLL void SetPosition(const glm::vec3 position);
      EXPORT_DLL glm::vec3 GetPosition() const;

      EXPORT_DLL void SetForwardDirection(const glm::vec3 forward);
      EXPORT_DLL glm::vec3 GetForwardDirection() const;

      EXPORT_DLL void SetUpDirection(const glm::vec3 up);
      EXPORT_DLL glm::vec3 GetUpDirection() const;

   private:
      Camera(const glm::ivec2& size);

      std::unique_ptr<Camera_impl> m_impl;

      friend class Scene_impl;
   };
}
