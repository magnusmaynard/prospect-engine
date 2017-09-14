#include "Camera_impl.h"
#include "EngineDefines.h"

using namespace Prospect;

Camera_impl::Camera_impl(Camera& parent, const glm::ivec2& size)
   :
   m_parent(parent),
   m_up(POS_Y)
{
   Resize(size);
}

void Camera_impl::LookAt(const glm::vec3 eyePosition, const glm::vec3 targetPosition)
{
   m_view = glm::lookAt(eyePosition, targetPosition, m_up);
}

glm::mat4 Camera_impl::GetViewMatrix() const
{
   return m_view;
}

glm::mat4 Camera_impl::GetProjectionMatrix() const
{
   return m_projection;
}

void Camera_impl::Resize(const glm::ivec2& size)
{
   m_size = size;

   float aspect = m_size.x / static_cast<float>(m_size.y);
   m_projection = glm::perspective(glm::radians(45.0f), aspect, 0.0001f, 10000.0f);
}
