#include "ProspectEngine_pch.h"

#include "Debug.h"
#include "Renderer/Pipeline/Shaders/Shader.h"
#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Frustum.h"

using namespace Prospect;
using namespace glm;


static DebugShader* m_shader;
static GLuint m_vao;
static GLuint m_buffer;
static std::vector<vec3> m_points1;
static std::vector<vec3> m_points2;

void Debug::CheckErrors()
{
#ifdef _DEBUG
   GLenum error;
   while ((error = glGetError()) != GL_NO_ERROR)
   {
      std::cerr << "Error: 0x" << std::hex << error << std::endl;
   };
#endif
}

void Debug::Points::Initialise(ShaderLibrary& shaderLibrary)
{
#ifdef _DEBUG
   m_shader = &shaderLibrary.GetDebugShader();

   glCreateVertexArrays(1, &m_vao);
#endif
}

void Debug::Points::Set1(std::vector<vec3>& points)
{
#ifdef _DEBUG
   m_points1 = points;
#endif
}

void Debug::Points::Set2(std::vector<vec3>& points)
{
#ifdef _DEBUG
   m_points2 = points;
#endif
}

void Debug::Points::Render()
{
   Render(m_points1, Color::Red());
   Render(m_points2, Color::Blue());
}

void Debug::Points::Render(std::vector<vec3>& points, const Color& color)
{
#ifdef _DEBUG
   if (!m_shader || points.size() == 0)
   {
      return;
   }

   //Reset buffers
   glDeleteBuffers(1, &m_buffer);
   glCreateBuffers(1, &m_buffer);

   //Create vertex buffer
   glNamedBufferStorage(
      m_buffer,
      points.size() * sizeof(glm::vec3),
      &points[0],
      0);

   glVertexArrayVertexBuffer(
      m_vao,
      0,
      m_buffer,
      0,
      sizeof(glm::vec3));

   glVertexArrayAttribFormat(
      m_vao,
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      0);

   glVertexArrayAttribBinding(m_vao, 0, 0);
   glEnableVertexArrayAttrib(m_vao, 0);

   //Draw
   m_shader->Bind();
   glBindVertexArray(m_vao);

   glUniform3f(0, color.R, color.G, color.B);
   glPointSize(10);
   glLineWidth(10);
   glDrawArrays(GL_LINES, 0, points.size());
   glPointSize(1);
   glLineWidth(1);
#endif
}

void Debug::Points::AddFrustumToPoints(std::vector<vec3>& points, const Frustum& frustum, const mat4& transform)
{
#ifdef _DEBUG
   const vec3 n0 = transform * vec4(frustum.Corners[0], 1);
   const vec3 n1 = transform * vec4(frustum.Corners[1], 1);
   const vec3 n2 = transform * vec4(frustum.Corners[3], 1);
   const vec3 n3 = transform * vec4(frustum.Corners[2], 1);

   const vec3 f0 = transform * vec4(frustum.Corners[4], 1);
   const vec3 f1 = transform * vec4(frustum.Corners[5], 1);
   const vec3 f2 = transform * vec4(frustum.Corners[7], 1);
   const vec3 f3 = transform * vec4(frustum.Corners[6], 1);

   points.push_back(n0);
   points.push_back(n1);
   points.push_back(n1);
   points.push_back(n2);
   points.push_back(n2);
   points.push_back(n3);
   points.push_back(n3);
   points.push_back(n0);

   points.push_back(f0);
   points.push_back(f1);
   points.push_back(f1);
   points.push_back(f2);
   points.push_back(f2);
   points.push_back(f3);
   points.push_back(f3);
   points.push_back(f0);

   points.push_back(n0);
   points.push_back(f0);
   points.push_back(n1);
   points.push_back(f1);
   points.push_back(n2);
   points.push_back(f2);
   points.push_back(n3);
   points.push_back(f3);
#endif
}

void Debug::Points::AddBoundsToPoints(std::vector<vec3>& points, const Bounds& bounds, const glm::mat4& transform)
{
#ifdef _DEBUG
   const vec3 n0 = transform * vec4(bounds.Max.x, bounds.Max.y, bounds.Min.z, 1);
   const vec3 n1 = transform * vec4(bounds.Min.x, bounds.Max.y, bounds.Min.z, 1);
   const vec3 n2 = transform * vec4(bounds.Min.x, bounds.Min.y, bounds.Min.z, 1);
   const vec3 n3 = transform * vec4(bounds.Max.x, bounds.Min.y, bounds.Min.z, 1);

   const vec3 f0 = transform * vec4(bounds.Max.x, bounds.Max.y, bounds.Max.z, 1);
   const vec3 f1 = transform * vec4(bounds.Min.x, bounds.Max.y, bounds.Max.z, 1);
   const vec3 f2 = transform * vec4(bounds.Min.x, bounds.Min.y, bounds.Max.z, 1);
   const vec3 f3 = transform * vec4(bounds.Max.x, bounds.Min.y, bounds.Max.z, 1);

   points.push_back(n0);
   points.push_back(n1);
   points.push_back(n1);
   points.push_back(n2);
   points.push_back(n2);
   points.push_back(n3);
   points.push_back(n3);
   points.push_back(n0);

   points.push_back(f0);
   points.push_back(f1);
   points.push_back(f1);
   points.push_back(f2);
   points.push_back(f2);
   points.push_back(f3);
   points.push_back(f3);
   points.push_back(f0);

   points.push_back(n0);
   points.push_back(f0);
   points.push_back(n1);
   points.push_back(f1);
   points.push_back(n2);
   points.push_back(f2);
   points.push_back(n3);
   points.push_back(f3);


#endif
}