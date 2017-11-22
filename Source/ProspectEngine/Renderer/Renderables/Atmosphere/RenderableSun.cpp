#include "ProspectEngine_pch.h"

#include "RenderableSun.h"
#include "Resources/Resources.h"
#include "Renderer/Shaders/ShaderFactory.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"

#include "Scene/Atmosphere_impl.h"

using namespace Prospect;
using namespace glm;

RenderableSun::RenderableSun(const GlobalUniformBuffers& globalUniformBuffers)
   :
   m_sunShader(ShaderFactory::CreateShader(
      Resources::SUN_VERTEX_SHADER,
      Resources::SUN_FRAGMENT_SHADER)),
   m_sunUniformBuffer("SunUniforms"),
   m_sunColor(1, 1, 1), //TODO:
   m_sunRadius(100),
   m_sunDistance(8000)
{
   globalUniformBuffers.Camera.Bind(m_sunShader);
   m_sunUniformBuffer.Bind(m_sunShader);

   CreateSun();
}

RenderableSun::~RenderableSun()
{
   glDeleteBuffers(1, &m_sunBuffer);
   glDeleteVertexArrays(1, &m_sunVAO);
}

void RenderableSun::CreateSun()
{
   //Creates a fan of points around a central vertex.
   const int segments = 24;
   const vec3 origin;
   const float decrement = pi<float>() * 2.f / segments;

   m_sunPoints.clear();
   m_sunPoints.reserve(segments + 2);
   m_sunPoints.push_back(origin);

   float angle = 0;
   for (int i = 0; i <= segments; i++)
   {
      m_sunPoints.push_back(vec3(sin(angle) * m_sunRadius, cos(angle) * m_sunRadius, 0));
      angle -= decrement;
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


void RenderableSun::UpdateUniforms(const Atmosphere_impl& atmosphere)
{
   vec3 toSun = -normalize(atmosphere.GetSunDirection());
   m_sunTranslation = translate(toSun * m_sunDistance);
   m_sunUniformBuffer.Update({ m_sunTranslation });
}

void RenderableSun::Render()
{
   m_sunShader.Bind();
   glBindVertexArray(m_sunVAO);
   glUniform3fv(4, 1, &m_sunColor[0]);
   glDrawArrays(GL_TRIANGLE_FAN, 0, m_sunPoints.size());
}
