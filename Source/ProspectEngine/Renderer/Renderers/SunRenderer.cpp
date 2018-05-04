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
   m_shader(shaderLibrary.GetSunShader())
{
   m_renderDataLibrary.SetInitialise(Initialise);
   m_renderDataLibrary.SetDispose(Dispose);
}

SunRenderer::~SunRenderer()
{
}

void SunRenderer::Initialise(SunRenderData& renderData)
{
   //Defaults
   renderData.Color = vec3(1, 1, 1);
   renderData.Radius = 10;
   renderData.Distance = 800;

   //Creates a fan of points around a central vertex.
   const int segments = 24;
   const vec3 origin;
   const float decrement = pi<float>() * 2.f / segments;

   renderData.Points.clear();
   renderData.Points.reserve(segments + 2);
   renderData.Points.push_back(origin);

   float angle = 0;
   for (int i = 0; i <= segments; i++)
   {
      renderData.Points.push_back(vec3(sin(angle) * renderData.Radius, cos(angle) * renderData.Radius, 0));
      angle -= decrement;
   }

   glCreateVertexArrays(1, &renderData.VAO);

   glCreateBuffers(1, &renderData.PointsBuffer);

   //Create vertex buffer.
   glNamedBufferStorage(
      renderData.PointsBuffer,
      renderData.Points.size() * sizeof(vec3),
      &renderData.Points[0],
      0);

   glVertexArrayVertexBuffer(
      renderData.VAO,
      0,
      renderData.PointsBuffer,
      0,
      sizeof(vec3));

   glVertexArrayAttribFormat(
      renderData.VAO,
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      0);

   glVertexArrayAttribBinding(renderData.VAO, 0, 0);
   glEnableVertexArrayAttrib(renderData.VAO, 0);

   //Set initialisation flag.
   renderData.Initialised = true;
}

void SunRenderer::Dispose(SunRenderData& renderData)
{
   glDeleteBuffers(1, &renderData.PointsBuffer);
   glDeleteVertexArrays(1, &renderData.VAO);
}

void SunRenderer::Render(const Atmosphere_impl& atmosphere)
{
   SunRenderData& renderData = m_renderDataLibrary.GetRenderData(atmosphere.GetId());

   //Update state.
   glDepthMask(GL_TRUE);
   glDisable(GL_DEPTH_TEST);
   glBlendFunc(GL_ONE, GL_ZERO);
   glEnable(GL_CULL_FACE);

   //TODO: if dirty
   const vec3 toSun = -normalize(atmosphere.GetSunDirection());
   renderData.Translation = translate(toSun * renderData.Distance);
   m_shader.Update({ renderData.Translation });

   m_shader.Bind();

   glBindVertexArray(renderData.VAO);
   glUniform3fv(4, 1, &renderData.Color[0]);

   glDrawArrays(GL_TRIANGLE_FAN, 0, renderData.Points.size());
}
