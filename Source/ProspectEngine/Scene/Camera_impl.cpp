#include "ProspectEngine_pch.h"

#include "Camera_impl.h"
#include "Engine/EngineDefines.h"

using namespace Prospect;
using namespace glm;

Camera_impl::Camera_impl(Camera& parent, const ivec2& size)
   :
   m_parent(parent),
   m_size(size),
   m_up(Defines::POS_Y),
   m_forward(Defines::POS_Z),
   m_near(Defaults::CAMERA_NEAR),
   m_far(Defaults::CAMERA_FAR),
   m_fov(Defaults::CAMERA_FOV),
   m_minAngle(Defaults::CAMERA_MIN_ANGLE),
   m_maxAngle(Defaults::CAMERA_MAX_ANGLE),
   m_aspectRatio(0),
   m_isPespective(true),
   m_viewIsDirty(true),
   m_projectionIsDirty(true)
{
   SetSize(m_size);
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

   m_aspectRatio = m_size.x / static_cast<float>(m_size.y);

   m_projectionIsDirty = true;
}

ivec2 Camera_impl::GetSize() const
{
   return m_size;
}

void Camera_impl::Turn(const vec2 delta)
{
   const float horizontal = delta.x * Defaults::CAMERA_SENSITIVITY;
   const float vertical = delta.y * Defaults::CAMERA_SENSITIVITY;

   //Horizontal rotation.
   m_forward = rotate(m_forward, radians(horizontal), m_up);

   //Vertical rotation.
   const vec3 newForward = rotate(m_forward, -radians(vertical), GetLeft());
   const float newAngle = degrees(glm::angle(m_up, newForward));

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

void Camera_impl::UpdateView() const
{
   if (m_viewIsDirty)
   {
      m_view = lookAt(m_position, m_position + m_forward, m_up);
      m_inverseView = inverse(m_view);

      m_viewIsDirty = false;
   }
}

void Camera_impl::UpdateProjectionsIfDirty() const
{
   if (m_projectionIsDirty)
   {
      m_projectionIsDirty = false;

      m_perspectiveProjection = perspective(
         radians(m_fov),
         m_aspectRatio,
         m_near,
         m_far);

      m_inversePerspectiveProjection = inverse(m_perspectiveProjection);

      m_orthographicProjection = ortho(
         m_size.x * -0.5f,
         m_size.x * 0.5f,
         m_size.y * -0.5f,
         m_size.y * 0.5f,
         m_near,
         m_far);
   }
}

mat4 Camera_impl::GetView() const
{
   UpdateView();

   return m_view;
}

mat4 Camera_impl::GetInverseView() const
{
   UpdateView();

   return m_inverseView;
}

mat4 Camera_impl::GetProjection() const
{
   if (m_isPespective)
   {
      return GetPerspectiveProjection();
   }

   return GetOrthographicProjection();
}

mat4 Camera_impl::GetPerspectiveProjection() const
{
   UpdateProjectionsIfDirty();

   return m_perspectiveProjection;
}

mat4 Camera_impl::GetInversePerspectiveProjection() const
{
   UpdateProjectionsIfDirty();

   return m_inversePerspectiveProjection;
}

mat4 Camera_impl::GetOrthographicProjection() const
{
   UpdateProjectionsIfDirty();

   return m_orthographicProjection;
}

float Camera_impl::GetNear() const
{
   return m_near;
}

float Camera_impl::GetFar() const
{
   return m_far;
}

float Camera_impl::GetFov() const
{
   return m_fov;
}

float Camera_impl::GetAspectRatio() const
{
   return m_aspectRatio;
}
