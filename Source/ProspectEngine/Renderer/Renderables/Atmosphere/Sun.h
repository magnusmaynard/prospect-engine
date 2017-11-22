#pragma once

#include "Renderer/Shaders/Shader.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/UniformBuffer.h"

namespace Prospect
{
   struct GlobalUniformBuffers;

   class Sun
   {
   public:
      Sun(const GlobalUniformBuffers& globalUniformBuffers);
      ~Sun();

      void Render();
      void UpdateUniforms(const Atmosphere_impl& atmosphere);

   private:
      void CreateSun();

      Shader& m_shader;
      UniformBuffer<SunUniforms> m_uniformBuffer;
      GLuint m_pointsBuffer;
      GLuint m_VAO;

      glm::mat4 m_translation;
      std::vector<glm::vec3> m_points;
      glm::vec3 m_color;
      float m_radius;
      float m_distance;
   };
}
