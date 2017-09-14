#pragma once
#include "Include/Camera.h"

#include "Camera_impl.h";

using namespace Prospect;

Camera::Camera(const glm::ivec2& size)
   :
   m_impl(std::make_unique<Camera_impl>(*this, size))
{
}

Camera::~Camera() = default;


Camera_impl& Camera::GetImpl()
{
   return *m_impl;
}

void Camera::LookAt(const glm::vec3 eyePosition, const glm::vec3 lookPosition)
{
   m_impl->LookAt(eyePosition, lookPosition);
}

void Camera::Resize(const glm::ivec2& size)
{
   m_impl->Resize(size);
}
