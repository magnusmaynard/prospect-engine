#pragma once
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "ShaderProgram.h"

namespace Prospect
{
   class Atmosphere
   {
   public:
      Atmosphere();
      ~Atmosphere();

      void Atmosphere::Draw(
         const glm::mat4& view,
         const glm::mat4& projection,
         const glm::vec2& resolution,
         const glm::vec3& sunDirection,
         const glm::vec3& eyePosition,
         const glm::vec3& earthPosition);

   private:
      ShaderProgram m_shader;

      GLint m_modelLocation = 0;
      GLint m_viewLocation = 0;
      GLint m_projectionLocation = 0;
      GLint m_timeLocation = 0;
      GLint m_resolutionLocation = 0;
      GLint m_sunDirectionLocation = 0;
      GLint m_eyePositionLocation = 0;
      GLint m_earthPositionLocation = 0;
   };
}
