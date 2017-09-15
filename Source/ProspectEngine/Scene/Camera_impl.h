#pragma once
#include "Include/Camera.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Prospect
{
   class Camera_impl
   {
   public:
      //Public
      void LookAt(const glm::vec3 eyePosition, const glm::vec3 targetPosition);
      void SetSize(const glm::ivec2& size);

      void SetPosition(const glm::vec3 position);
      glm::vec3 GetPosition() const;

      void SetForward(const glm::vec3 forward);
      glm::vec3 GetForward() const;

      void SetUp(const glm::vec3 up);
      glm::vec3 GetUp() const;

      //Internal
      Camera_impl(Camera& parent, const glm::ivec2& size);

      glm::mat4 GetViewMatrix() const;
      glm::mat4 GetProjectionMatrix() const;

   private:
      void UpdateViewMatrix();
      void UpdateProjectionMatrix();

      Camera& m_parent;

      glm::vec3 m_position;
      glm::vec3 m_up;
      glm::vec3 m_forward;
      glm::ivec2 m_size;

      glm::mat4 m_projection;
      glm::mat4 m_view;
   };
}