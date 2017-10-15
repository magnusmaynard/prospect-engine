#include "ProspectEngine_pch.h"

#include "Renderer/VertexData.h"

#include "Scene/Mesh_impl.h"

using namespace Prospect;

VertexData::VertexData(Mesh_impl& mesh)
   :
   m_mesh(mesh)
{
   glCreateVertexArrays(1, &m_VAO);
}

VertexData::~VertexData()
{
   glDeleteBuffers(BUFFER_COUNT, m_buffers);
   glDeleteVertexArrays(1, &m_VAO);
}

VertexData::VertexData(VertexData&& other)
   :
   m_VAO(other.m_VAO),
   m_mesh(other.m_mesh)
{
   //Move.
   std::copy(m_buffers, m_buffers + BUFFER_COUNT, other.m_buffers);

   //Release.
   other.m_VAO = GL_NULL;
   std::fill(other.m_buffers, other.m_buffers + BUFFER_COUNT, GL_NULL);
}


void VertexData::UpdateBuffers()
{
   //Reset buffers
   glDeleteBuffers(BUFFER_COUNT, m_buffers);
   glCreateBuffers(BUFFER_COUNT, m_buffers);

   //Create vertex buffer.
   auto& vertices = m_mesh.GetVertices();

   glNamedBufferStorage(
      m_buffers[BUFFER_VERTICES],
      vertices.size() * sizeof(glm::vec3),
      &vertices[0],
      0);

   glVertexArrayVertexBuffer(
      m_VAO,
      0,
      m_buffers[BUFFER_VERTICES],
      0,
      sizeof(glm::vec3));

   glVertexArrayAttribFormat(
      m_VAO,
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      0);

   glVertexArrayAttribBinding(m_VAO, 0, 0);
   glEnableVertexArrayAttrib(m_VAO, 0);

   //Create index buffer.
   auto& indices = m_mesh.GetIndices();

   glNamedBufferStorage(
      m_buffers[BUFFER_INDICES],
      indices.size() * sizeof(unsigned int),
      &indices[0],
      0);

   glVertexArrayElementBuffer(
      m_VAO,
      m_buffers[BUFFER_INDICES]);
}


void VertexData::Render()
{
   if (m_mesh.GetVertices().size() > 0)
   {
      glBindVertexArray(m_VAO);

      if (m_mesh.IsDirty())
      {
         m_mesh.SetIsDirty(false);

         UpdateBuffers();
      }

      glDrawElements(GL_TRIANGLES, m_mesh.GetIndices().size(), GL_UNSIGNED_INT, 0);
   }
}