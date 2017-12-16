#include "ProspectEngine_pch.h"

#include "Sun.h"

#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Scene/Atmosphere_impl.h"

using namespace Prospect;
using namespace glm;

Sun::Sun(ShaderLibrary& shaderLibrary)
   :
   m_shader(shaderLibrary.GetSunShader()),
   m_color(1, 1, 1), //TODO:
   m_radius(100),
   m_distance(8000)
{
   CreateSun();
}

Sun::~Sun()
{
   glDeleteBuffers(1, &m_pointsBuffer);
   glDeleteVertexArrays(1, &m_VAO);
}

void Sun::CreateSun()
{
   //Creates a fan of points around a central vertex.
   const int segments = 24;
   const vec3 origin;
   const float decrement = pi<float>() * 2.f / segments;

   m_points.clear();
   m_points.reserve(segments + 2);
   m_points.push_back(origin);

   float angle = 0;
   for (int i = 0; i <= segments; i++)
   {
      m_points.push_back(vec3(sin(angle) * m_radius, cos(angle) * m_radius, 0));
      angle -= decrement;
   }

   glCreateBuffers(1, &m_pointsBuffer);

   //Create vertex buffer.
   glNamedBufferStorage(
      m_pointsBuffer,
      m_points.size() * sizeof(vec3),
      &m_points[0],
      0);

   glVertexArrayVertexBuffer(
      m_VAO,
      0,
      m_pointsBuffer,
      0,
      sizeof(vec3));

   glVertexArrayAttribFormat(
      m_VAO,
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      0);

   glVertexArrayAttribBinding(m_VAO, 0, 0);
   glEnableVertexArrayAttrib(m_VAO, 0);
}


void Sun::UpdateUniforms(const Atmosphere_impl& atmosphere)
{
   vec3 toSun = -normalize(atmosphere.GetSunDirection());
   m_translation = translate(toSun * m_distance);

   m_shader.Update({ m_translation });
}

void Sun::Render()
{
   m_shader.Bind();
   glBindVertexArray(m_VAO);
   glUniform3fv(4, 1, &m_color[0]);
   glDrawArrays(GL_TRIANGLE_FAN, 0, m_points.size());
}
