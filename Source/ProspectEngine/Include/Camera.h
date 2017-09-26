#pragma once

#include <memory>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Prospect
{
   class Camera_impl;

   class Camera
   {
   public:
      ~Camera();

      void SetSize(const glm::ivec2& size);

      void LookAt(const glm::vec3 eyePosition, const glm::vec3 targetPosition);

      void SetPosition(const glm::vec3 position);
      glm::vec3 GetPosition() const;

      void SetForwardDirection(const glm::vec3 forward);
      glm::vec3 GetForwardDirection() const;

      void SetUpDirection(const glm::vec3 up);
      glm::vec3 GetUpDirection() const;

   private:
      Camera(const glm::ivec2& size);

      std::unique_ptr<Camera_impl> m_impl;

      friend class Scene_impl;
   };
}
