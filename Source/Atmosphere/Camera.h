#pragma once

#include <glm/vec3.hpp>

class Camera
{
public:
   Camera(const glm::ivec2& size)
      :
      m_up(0, 1, 0)
   {
      Resize(size);
   }

   void LookAt(const glm::vec3 eyePosition, const glm::vec3 targetPosition)
   {
      m_view = glm::lookAt(eyePosition, targetPosition, m_up);
   }

   glm::mat4 GetViewMatrix() const
   {
      return m_view;
   }

   glm::mat4 GetProjectionMatrix() const
   {
      return m_projection;
   }

   void Resize(const glm::ivec2& size)
   {
      m_size = size;

      float aspect = m_size.x / static_cast<float>(m_size.y);
      m_projection = glm::perspective(glm::radians(45.0f), aspect, 0.0001f, 10000.0f);
   }

private:
   glm::vec3 m_up;
   glm::ivec2 m_size;

   glm::mat4 m_projection;
   glm::mat4 m_view;
};