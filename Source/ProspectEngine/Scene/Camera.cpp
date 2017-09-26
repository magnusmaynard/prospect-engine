#pragma once
#include "Include/Camera.h"

#include "Camera_impl.h"

using namespace Prospect;

Camera::Camera(const glm::ivec2& size)
   :
   m_impl(std::make_unique<Camera_impl>(*this, size))
{
}

Camera::~Camera() = default;

void Camera::SetSize(const glm::ivec2& size)
{
   m_impl->SetSize(size);
}

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

void Camera::SetForwardDirection(const glm::vec3 forward)
{
   m_impl->SetForward(forward);
}

glm::vec3 Camera::GetForwardDirection() const
{
   return m_impl->GetForward();
}

void Camera::SetUpDirection(const glm::vec3 up)
{
   m_impl->SetUp(up);
}

glm::vec3 Camera::GetUpDirection() const
{
   return m_impl->GetUp();
}
