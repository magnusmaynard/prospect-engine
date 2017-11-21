#pragma once
#include "Renderer/Shaders/Shader.h"
#include "Renderer/Renderables/IRenderable.h"
#include "Renderer/Uniforms/UniformBlocks.h"
#include "Renderer/Uniforms/UniformBuffer.h"

namespace Prospect
{
   class Atmosphere_impl;
   struct GlobalUniformBuffers;

   class RenderableAtmosphere : public IRenderable
   {
   public:
      RenderableAtmosphere(const GlobalUniformBuffers& globalUniformBuffers, const Atmosphere_impl& atmosphere);
      ~RenderableAtmosphere();

      void Render() override;
      void MakeDirty() override;

   private:
      void CreateSun();
      void UpdateUniformsIfDirty();

      mutable bool m_isDirty;

      Shader& m_atmosphereShader;
      UniformBuffer<AtmosphereUniforms> m_atmosphereUniformBuffer;
      const Atmosphere_impl& m_atmosphere;

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
