#include "ProspectEngine_pch.h"

#include "RenderableAtmosphere.h"
#include "Resources/Resources.h"
#include "Renderer/Shaders/ShaderFactory.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"

#include "Scene/Atmosphere_impl.h"

using namespace Prospect;
using namespace glm;

RenderableAtmosphere::RenderableAtmosphere(
   const GlobalUniformBuffers& globalUniformBuffers,
   const Atmosphere_impl& atmosphere)
   :
   m_atmosphereShader(ShaderFactory::CreateShader(
      Resources::ATMOSPHERE_VERTEX_SHADER,
      Resources::ATMOSPHERE_FRAGMENT_SHADER)),
   m_sunShader(ShaderFactory::CreateShader(
      Resources::SUN_VERTEX_SHADER,
      Resources::SUN_FRAGMENT_SHADER)),
   m_atmosphereUniformBuffer("AtmosphereUniforms"),
   m_atmosphere(atmosphere),
   m_sunUniformBuffer("SunUniforms"),
   m_sunColor(1, 0, 0),
   m_sunRadius(20)
{
   //Atmosphere
   globalUniformBuffers.Camera.Bind(m_atmosphereShader);
   globalUniformBuffers.DirectionalLight.Bind(m_atmosphereShader);

   m_atmosphereUniformBuffer.Bind(m_atmosphereShader);
   m_atmosphereUniformBuffer.Update({
      m_atmosphere.GetAltitude()
   });

   //Sun
   globalUniformBuffers.Camera.Bind(m_sunShader);
   m_sunUniformBuffer.Bind(m_sunShader);

   CreateSun();
   UpdateSunTranslation();
}

RenderableAtmosphere::~RenderableAtmosphere()
{
   glDeleteBuffers(1, &m_sunBuffer);
   glDeleteVertexArrays(1, &m_sunVAO);
}

void RenderableAtmosphere::CreateSun()
{
   //Creates a fan of points around a central vertex.
   const int segments = 24;
   const vec3 origin;
   const float increment = pi<float>() * 2.f / segments;

   m_sunPoints.clear();
   m_sunPoints.reserve(segments + 2);
   m_sunPoints.push_back(origin);

   float angle = 0;
   for (int i = 0; i <= segments; i++)
   {
      m_sunPoints.push_back(vec3(sin(angle) * m_sunRadius, cos(angle) * m_sunRadius, -0.2));
      angle += increment;
   }

   glCreateBuffers(1, &m_sunBuffer);

   //Create vertex buffer.
   glNamedBufferStorage(
      m_sunBuffer,
      m_sunPoints.size() * sizeof(vec3),
      &m_sunPoints[0],
      0);

   glVertexArrayVertexBuffer(
      m_sunVAO,
      0,
      m_sunBuffer,
      0,
      sizeof(vec3));

   glVertexArrayAttribFormat(
      m_sunVAO,
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      0);

   glVertexArrayAttribBinding(m_sunVAO, 0, 0);
   glEnableVertexArrayAttrib(m_sunVAO, 0);
}


void RenderableAtmosphere::UpdateSunTranslation()
{
   const float distance = 1000;
   const vec3 direction = normalize(vec3(0, 1, -1));//m_atmosphere.GetSunDirection();
   m_sunTranslation = translate(direction * distance);
   m_sunUniformBuffer.Update({ m_sunTranslation });
}

void RenderableAtmosphere::Render()
{
   glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);

   m_sunShader.Bind();
   glBindVertexArray(m_sunVAO);


   glUniform3fv(4, 1, &m_sunColor[0]);
   glDrawArrays(GL_TRIANGLE_FAN, 0, m_sunPoints.size());

   m_atmosphereShader.Bind();
   glDrawArrays(GL_TRIANGLES, 0, 6);
}
