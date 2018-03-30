#include "ProspectEngine_pch.h"

#include "SunRenderer.h"

#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Uniforms/GlobalUniformBuffers.h"
#include "Scene/Atmosphere_impl.h"
#include "Renderer/Debugger/Debug.h"

using namespace Prospect;
using namespace glm;

SunRenderer::SunRenderer(ShaderLibrary& shaderLibrary)
   :
   m_shader(shaderLibrary.GetSunShader()),
   m_renderDataLibrary(InitialiseSun, DisposeSun)
{
}

SunRenderer::~SunRenderer()
{
}

void SunRenderer::InitialiseSun(SunRenderData& renderable)
{
   //Defaults
   renderable.Color = vec3(1, 1, 1);
   renderable.Radius = 100;
   renderable.Distance = 8000;

   //Creates a fan of points around a central vertex.
   const int segments = 24;
   const vec3 origin;
   const float decrement = pi<float>() * 2.f / segments;

   renderable.Points.clear();
   renderable.Points.reserve(segments + 2);
   renderable.Points.push_back(origin);

   float angle = 0;
   for (int i = 0; i <= segments; i++)
   {
      renderable.Points.push_back(vec3(sin(angle) * renderable.Radius, cos(angle) * renderable.Radius, 0));
      angle -= decrement;
   }

   glCreateVertexArrays(1, &renderable.VAO);

   glCreateBuffers(1, &renderable.PointsBuffer);

   //Create vertex buffer.
   glNamedBufferStorage(
      renderable.PointsBuffer,
      renderable.Points.size() * sizeof(vec3),
      &renderable.Points[0],
      0);

   glVertexArrayVertexBuffer(
      renderable.VAO,
      0,
      renderable.PointsBuffer,
      0,
      sizeof(vec3));

   glVertexArrayAttribFormat(
      renderable.VAO,
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      0);

   glVertexArrayAttribBinding(renderable.VAO, 0, 0);
   glEnableVertexArrayAttrib(renderable.VAO, 0);
}

void SunRenderer::DisposeSun(SunRenderData& renderable)
{
   glDeleteBuffers(1, &renderable.PointsBuffer);
   glDeleteVertexArrays(1, &renderable.VAO);
}

void SunRenderer::Render(const Atmosphere_impl& atmosphere)
{
   SunRenderData& renderData = m_renderDataLibrary.GetRenderData(atmosphere.GetId());

   //TODO: if dirty
   vec3 toSun = -normalize(atmosphere.GetSunDirection());
   renderData.Translation = translate(toSun * renderData.Distance);
   m_shader.Update({ renderData.Translation });

   glEnable(GL_DEPTH_TEST);

   m_shader.Bind();

   glBindVertexArray(renderData.VAO);
   glUniform3fv(4, 1, &renderData.Color[0]);

   glDrawArrays(GL_TRIANGLE_FAN, 0, renderData.Points.size());
   Debug::CheckErrors();
}
