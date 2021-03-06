#include "ProspectEngine_pch.h"

#include "Include/Camera.h"

#include "Camera_impl.h"

using namespace Prospect;

Camera::Camera(const glm::ivec2& size)
   :
   m_impl(std::make_unique<Camera_impl>(*this, size))
{
}

Camera::~Camera() = default;

void Camera::LookAt(const glm::vec3 eyePosition, const glm::vec3 lookPosition)
{
   m_impl->LookAt(eyePosition, lookPosition);
}

void Camera::SetPosition(const glm::vec3 position)
{
   m_impl->SetPosition(position);
}

glm::vec3 Camera::GetPosition() const
{
   return m_impl->GetPosition();
}

void Camera::SetForward(const glm::vec3 forward)
{
   m_impl->SetForward(forward);
}

glm::vec3 Camera::GetForward() const
{
   return m_impl->GetForward();
}

void Camera::SetUp(const glm::vec3 up)
{
   m_impl->SetUp(up);
}

glm::vec3 Camera::GetUp() const
{
   return m_impl->GetUp();
}

glm::vec3 Camera::GetLeft() const
{
   return m_impl->GetLeft();
}

glm::ivec2 Camera::GetSize() const
{
   return m_impl->GetSize();
}
