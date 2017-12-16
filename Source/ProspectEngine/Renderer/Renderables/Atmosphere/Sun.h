#pragma once

#include "Renderer/Pipeline/Shaders/Shader.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Pipeline/Shaders/SunShader.h"

namespace Prospect
{
   class ShaderLibrary;
   struct GlobalUniformBuffers;

   class Sun
   {
   public:
      Sun(ShaderLibrary& shaderLibrary);
      ~Sun();

      void Render();
      void UpdateUniforms(const Atmosphere_impl& atmosphere);

   private:
      void CreateSun();

      SunShader& m_shader;
      GLuint m_pointsBuffer;
      GLuint m_VAO;

      glm::mat4 m_translation;
      std::vector<glm::vec3> m_points;
      glm::vec3 m_color;
      float m_radius;
      float m_distance;
   };
}
