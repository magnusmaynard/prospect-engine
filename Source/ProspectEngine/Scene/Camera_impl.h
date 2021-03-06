#pragma once
#include "Include/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Prospect
{
   class Camera_impl
   {
   public:
      //Public
      void LookAt(const glm::vec3 eyePosition, const glm::vec3 targetPosition);

      void SetPosition(const glm::vec3 position);
      glm::vec3 GetPosition() const;

      void SetForward(const glm::vec3 forward);
      glm::vec3 GetForward() const;

      void SetUp(const glm::vec3 up);
      glm::vec3 GetUp() const;

      glm::vec3 GetLeft() const;

      //Internal
      Camera_impl(Camera& parent, const glm::ivec2& size);

      glm::ivec2 GetSize() const;
      void SetSize(const glm::ivec2& size);

      void Turn(const glm::vec2 delta);

      glm::mat4 GetView() const;
      glm::mat4 GetInverseView() const;
      glm::mat4 GetProjection() const;
      glm::mat4 GetPerspectiveProjection() const;
      glm::mat4 GetInversePerspectiveProjection() const;
      glm::mat4 GetOrthographicProjection() const;
      float GetNear() const;
      float GetFar() const;
      float GetFov() const;
      float GetAspectRatio() const;

   private:
      void UpdateView() const;
      void UpdateProjectionsIfDirty() const;

      Camera& m_parent;

      glm::vec3 m_position;
      glm::vec3 m_up;
      glm::vec3 m_forward;
      glm::ivec2 m_size;
      float m_near;
      float m_far;
      float m_fov; //Vertical.
      float m_aspectRatio;

      float m_minAngle;
      float m_maxAngle;

      bool m_isPespective;

      mutable bool m_viewIsDirty;
      mutable glm::mat4 m_view;
      mutable glm::mat4 m_inverseView;

      mutable bool m_projectionIsDirty;
      mutable glm::mat4 m_perspectiveProjection;
      mutable glm::mat4 m_inversePerspectiveProjection;
      mutable glm::mat4 m_orthographicProjection;
   };
}