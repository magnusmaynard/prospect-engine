#pragma once
#include "Renderer/Shaders/Shader.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/UniformBuffer.h"

namespace Prospect
{
   struct GlobalUniformBuffers;

   class RenderableSun
   {
   public:
      RenderableSun(const GlobalUniformBuffers& globalUniformBuffers);
      ~RenderableSun();

      void Render();
      void UpdateUniforms(const Atmosphere_impl& atmosphere);

   private:
      void CreateSun();

      glm::mat4 m_sunTranslation;
      Shader& m_sunShader;
      UniformBuffer<SunUniforms> m_sunUniformBuffer;
      GLuint m_sunBuffer;
      GLuint m_sunVAO;
      std::vector<glm::vec3> m_sunPoints;
      glm::vec3 m_sunColor;
      float m_sunRadius;
      float m_sunDistance;
   };
}
