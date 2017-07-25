#include "Camera.h"

using namespace Prospect;

Camera::Camera(const glm::ivec2& size):
   m_up(0, 1, 0)
{
   Resize(size);
}

void Camera::LookAt(const glm::vec3 eyePosition, const glm::vec3 targetPosition)
{
   m_view = glm::lookAt(eyePosition, targetPosition, m_up);
}

glm::mat4 Camera::GetViewMatrix() const
{
   return m_view;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
   return m_projection;
}

void Camera::Resize(const glm::ivec2& size)
{
   m_size = size;

   float aspect = m_size.x / static_cast<float>(m_size.y);
   m_projection = glm::perspective(glm::radians(45.0f), aspect, 0.0001f, 10000.0f);
}
