#include "ProspectEngine_pch.h"

#include "Camera_impl.h"
#include "EngineDefines.h"

using namespace Prospect;
using namespace glm;

Camera_impl::Camera_impl(Camera& parent, const ivec2& size)
   :
   m_parent(parent),
   m_size(size),
   m_up(POS_Y),
   m_forward(POS_Z),
   m_minAngle(DEFAULT_CAMERA_MIN_ANGLE),
   m_maxAngle(DEFAULT_CAMERA_MAX_ANGLE),
   m_viewIsDirty(true),
   m_projectionIsDirty(true)
{
}

void Camera_impl::LookAt(const vec3 eyePosition, const vec3 targetPosition)
{
   m_position = eyePosition;
   m_forward = normalize(targetPosition - eyePosition);

   m_viewIsDirty = true;
}

void Camera_impl::SetSize(const ivec2& size)
{
   if (m_size.x > 0 && m_size.y > 0)
   {
      m_size = size;
   }
   else
   {
      m_size = ivec2(1, 1);
   }

   m_projectionIsDirty = true;
}

ivec2 Camera_impl::GetSize() const
{
   return m_size;
}

void Camera_impl::Turn(const vec2 delta)
{
   float horizontal = delta.x * DEFAULT_CAMERA_SENSITIVITY;
   float vertical = delta.y * DEFAULT_CAMERA_SENSITIVITY;

   //Horizontal rotation.
   m_forward = rotate(m_forward, radians(horizontal), m_up);

   //Vertical rotation.
   vec3 newForward = rotate(m_forward, -radians(vertical), GetLeft());
   float newAngle = degrees(glm::angle(m_up, newForward));

   if (newAngle > m_minAngle && newAngle < m_maxAngle)
   {
      m_forward = newForward;
   }

   m_viewIsDirty = true;
}

void Camera_impl::SetPosition(const vec3 position)
{
   m_position = position;

   m_viewIsDirty = true;
}

vec3 Camera_impl::GetPosition() const
{
   return m_position;
}

void Camera_impl::SetForward(const vec3 forward)
{
   m_forward = forward;

   m_viewIsDirty = true;
}

vec3 Camera_impl::GetForward() const
{
   return m_forward;
}

void Camera_impl::SetUp(const vec3 up)
{
   m_up = up;

   m_viewIsDirty = true;
}

vec3 Camera_impl::GetUp() const
{
   return m_up;
}

vec3 Camera_impl::GetLeft() const
{
   return cross(m_up, m_forward);
}

void Camera_impl::UpdateViewMatrix() const
{
   if (m_viewIsDirty)
   {
      m_view = lookAt(m_position, m_position + m_forward, m_up);

      m_viewIsDirty = false;
   }
}

void Camera_impl::UpdateProjectionMatrix() const
{
   if (m_projectionIsDirty)
   {
      float aspect = m_size.x / static_cast<float>(m_size.y);

      m_projection = perspective(
         radians(DEFAULT_CAMERA_FOV),
         aspect,
         DEFAULT_CAMERA_NEAR,
         DEFAULT_CAMERA_FAR);

      m_projectionIsDirty = false;
   }
}

mat4 Camera_impl::GetViewMatrix() const
{
   UpdateViewMatrix();

   return m_view;
}

mat4 Camera_impl::GetProjectionMatrix() const
{
   UpdateProjectionMatrix();

   return m_projection;
}
