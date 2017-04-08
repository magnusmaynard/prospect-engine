#pragma once
#include "Object3D.h"

Object3D::Object3D(
   const std::vector<glm::vec3>& points,
   const std::vector<unsigned int>& indices,
   const std::vector<glm::vec3>& normals)
   :
   m_shader("object3D.vs.glsl", "object3D.fs.glsl"),
   m_points(std::move(points)),
   m_indices(std::move(indices)),
   m_normals(std::move(normals))
{
   m_modelLocation = m_shader.GetUniformLocation("model");
   m_viewLocation = m_shader.GetUniformLocation("view");
   m_projectionLocation = m_shader.GetUniformLocation("projection");
   m_sunDirectionLocation = m_shader.GetUniformLocation("sunDirection");

   glCreateVertexArrays(1, &m_VAO);
   glBindVertexArray(m_VAO);

   glCreateBuffers(BUFFER_COUNT, m_buffers);

   //Initialize point buffer.
   glNamedBufferStorage(
      m_buffers[BUFFER_POINT], m_points.size() * 3 * sizeof(float), &m_points[0], 0);
   //Bind vertex buffer to vertex array.
   glVertexArrayVertexBuffer(m_VAO, 0, m_buffers[BUFFER_POINT], 0, sizeof(glm::vec3));
   //Specify the format of the atrribute.
   glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
   //Specify which vertex buffer binding to use for the attribute.
   glVertexArrayAttribBinding(m_VAO, 0, 0);
   //Enable attribute.
   glEnableVertexArrayAttrib(m_VAO, 0);

   //Initialize index buffer.
   glNamedBufferStorage(
      m_buffers[BUFFER_INDEX], m_indices.size() * sizeof(unsigned int), &m_indices[0], 0);
   //Bind element buffer to vertex array.
   glVertexArrayElementBuffer(m_VAO, m_buffers[BUFFER_INDEX]);

   //Initialize normal buffer.
   glNamedBufferStorage(
      m_buffers[BUFFER_NORMAL], m_normals.size() * 3 * sizeof(float), &m_normals[0], 0);
   glVertexArrayVertexBuffer(m_VAO, 1, m_buffers[BUFFER_NORMAL], 0, sizeof(glm::vec3));
   glVertexArrayAttribFormat(m_VAO, 1, 3, GL_FLOAT, GL_FALSE, 0);
   glVertexArrayAttribBinding(m_VAO, 1, 0);
   glEnableVertexArrayAttrib(m_VAO, 1);
}

Object3D::~Object3D()
{
   //Dispose.
   glDeleteBuffers(BUFFER_COUNT, m_buffers);
   glDeleteVertexArrays(1, &m_VAO);
}

void Object3D::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& sunDirection)
{
   //Bind.
   m_shader.Use();
   glBindVertexArray(m_VAO);
   glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BUFFER_POINT]);

   //Uniforms.
   glUniformMatrix4fv(m_modelLocation, 1, GL_FALSE, &m_transform[0][0]);
   glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, &view[0][0]);
   glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, &projection[0][0]);

   //TODO: remove this.
   glUniform3fv(m_sunDirectionLocation, 1, &sunDirection[0]);


   //Draw.
   //glDrawArrays(GL_POINTS, 0, m_points.size());
   //glDrawArrays(GL_TRIANGLES, 0, m_points.size());
   glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

   //Unbind.
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Object3D::Transform(const glm::mat4& transform)
{
   m_transform *= transform;
}
