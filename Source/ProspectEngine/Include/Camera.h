#pragma once

namespace Prospect
{
   class Camera_impl;

   class Camera
   {
   public:
      ~Camera();

      void LookAt(const glm::vec3 eyePosition, const glm::vec3 targetPosition);

      void SetPosition(const glm::vec3 position);
      glm::vec3 GetPosition() const;

      void SetForward(const glm::vec3 forward);
      glm::vec3 GetForward() const;

      void SetUp(const glm::vec3 up);
      glm::vec3 GetUp() const;

      glm::vec3 Camera::GetLeft() const;

      glm::ivec2 Camera::GetSize() const;

   private:
      Camera(const glm::ivec2& size);

      std::unique_ptr<Camera_impl> m_impl;

      friend class Scene_impl;
   };
}
