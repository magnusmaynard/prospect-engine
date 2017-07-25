#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Prospect
{
   class Camera
   {
   public:
      Camera(const glm::ivec2& size);
      void LookAt(const glm::vec3 eyePosition, const glm::vec3 targetPosition);
      glm::mat4 GetViewMatrix() const;
      glm::mat4 GetProjectionMatrix() const;
      void Resize(const glm::ivec2& size);

   private:
      glm::vec3 m_up;
      glm::ivec2 m_size;
      glm::mat4 m_projection;
      glm::mat4 m_view;
   };
}