#include "ProspectEngine_pch.h"

#include "Atmosphere.h"

using namespace Prospect;

Atmosphere::Atmosphere()
{
   m_shader.AddVertexShader("atmosphere");
   m_shader.AddFragmentShader("atmosphere");
   m_shader.Compile();

   m_viewLocation = m_shader.GetUniformLocation("view");
   m_projectionLocation = m_shader.GetUniformLocation("projection");
   m_timeLocation = m_shader.GetUniformLocation("time");
   m_resolutionLocation = m_shader.GetUniformLocation("resolution");
   m_sunDirectionLocation = m_shader.GetUniformLocation("sunDirection");
   m_eyePositionLocation = m_shader.GetUniformLocation("eyePosition");
   m_earthPositionLocation = m_shader.GetUniformLocation("earthPosition");
}

Atmosphere::~Atmosphere()
{
}

void Atmosphere::Draw(
   const glm::mat4& view,
   const glm::mat4& projection,
   const glm::vec2& resolution,
   const glm::vec3& sunDirection,
   const glm::vec3& eyePosition,
   const glm::vec3& earthPosition)
{
   m_shader.Bind();
   
   glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, &view[0][0]);
   glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, &projection[0][0]);
   glUniform2fv(m_resolutionLocation, 1, &resolution[0]);
   glUniform3fv(m_sunDirectionLocation, 1, &sunDirection[0]);
   glUniform3fv(m_eyePositionLocation, 1, &eyePosition[0]);
   glUniform3fv(m_earthPositionLocation, 1, &earthPosition[0]);

   glDrawArrays(GL_TRIANGLES, 0, 6);
}
