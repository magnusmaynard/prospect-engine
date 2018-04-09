#include "ProspectEngine_pch.h"

#include "Debug.h"
#include "Renderer/Pipeline/Shaders/Shader.h"
#include "Renderer/Pipeline/ShaderLibrary.h"

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

void  Debug::Points::Initialise(ShaderLibrary& shaderLibrary)
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
   Render(m_points1);
   Render(m_points2);
}

void Debug::Points::Render(std::vector<vec3>& points)
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
   glPointSize(10);
   glDrawArrays(GL_POINTS, 0, points.size());
#endif
}
