#include "Camera_impl.h"
#include "EngineDefines.h"

using namespace Prospect;
using namespace glm;

Camera_impl::Camera_impl(Camera& parent, const ivec2& size)
   :
   m_parent(parent),
   m_size(size),
   m_up(POS_Y),
   m_forward(POS_Z)
{
   UpdateViewMatrix();
   UpdateProjectionMatrix();
}

void Camera_impl::LookAt(const vec3 eyePosition, const vec3 targetPosition)
{
   m_position = eyePosition;
   m_forward = normalize(targetPosition - eyePosition);

   UpdateViewMatrix();
}

void Camera_impl::SetSize(const ivec2& size)
{
   m_size = size;

   UpdateProjectionMatrix();
}

void Camera_impl::SetPosition(const vec3 position)
{
   m_position = position;

   UpdateViewMatrix();
}

vec3 Camera_impl::GetPosition() const
{
   return m_position;
}

void Camera_impl::SetForward(const vec3 forward)
{
   m_forward = forward;

   UpdateViewMatrix();
}

vec3 Camera_impl::GetForward() const
{
   return m_forward;
}

void Camera_impl::SetUp(const vec3 up)
{
   m_up = up;

   UpdateViewMatrix();
}

vec3 Camera_impl::GetUp() const
{
   return m_up;
}

void Camera_impl::UpdateViewMatrix()
{
   m_view = lookAt(m_position, m_position + m_forward, m_up);
}

void Camera_impl::UpdateProjectionMatrix()
{
   float aspect = m_size.x / static_cast<float>(m_size.y);

   m_projection = perspective(
      radians(DEFAULT_CAMERA_FOV),
      aspect,
      DEFAULT_CAMERA_NEAR,
      DEFAULT_CAMERA_FAR);
}

mat4 Camera_impl::GetViewMatrix() const
{
   return m_view;
}

mat4 Camera_impl::GetProjectionMatrix() const
{
   return m_projection;
}
