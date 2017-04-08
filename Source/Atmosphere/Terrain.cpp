#pragma once
#include "Terrain.h"

Terrain::Terrain()
   :
   m_shader("terrain.vs.glsl", "terrain.fs.glsl")
{
   GenerateSphere();

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
   glVertexArrayAttribBinding(m_VAO, 1, 1);
   glEnableVertexArrayAttrib(m_VAO, 1);
}

Terrain::~Terrain()
{
   //Dispose.
   glDeleteBuffers(BUFFER_COUNT, m_buffers);
   glDeleteVertexArrays(1, &m_VAO);
}

void Terrain::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& sunDirection)
{
   //Bind.
   m_shader.Use();
   glBindVertexArray(m_VAO);
   glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BUFFER_POINT]);

   //Uniforms.
   glUniformMatrix4fv(m_modelLocation, 1, GL_FALSE, &m_transform[0][0]);
   glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, &view[0][0]);
   glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, &projection[0][0]);
   glUniform3fv(m_sunDirectionLocation, 1, &sunDirection[0]);

   //Draw.
   glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

   //Unbind.
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Terrain::Transform(const glm::mat4& transform)
{
   m_transform *= transform;
}

void Terrain::GenerateSphere()
{
   const int FACE_COUNT = 6;
   const glm::vec3 ORIGIN = glm::vec3(0, 0, 0); //TODO: earthPosition

   float radius = 1000.0;
   float size = 1.0;
   float halfSize = 1.0 * 0.5;
   int sectionCount = 100;
   float sizePerSection = size / sectionCount;
   int pointsPerRow = sectionCount + 1;
   int pointsPerFace = pointsPerRow * pointsPerRow;
   int pointsPerObject = FACE_COUNT * pointsPerFace;

   //Resize containers.
   m_points.resize(pointsPerObject);
   m_indices.resize(pointsPerObject * 6);
   m_normals.resize(pointsPerObject);

   //Points.
   for (int y = 0; y <= sectionCount; y++)
   {
      int currentRow = y * pointsPerRow;

      for (int x = 0; x <= sectionCount; x++)
      {
         //Flip m_points along y axis to make face m_normals point outwards.
         int xReverse = (sectionCount - x);

         //Front.
         m_points[x + currentRow + pointsPerFace * 0] = glm::vec3(
            x * sizePerSection - halfSize,
            y * sizePerSection - halfSize,
            halfSize);

         //Back.
         m_points[x + currentRow + pointsPerFace * 1] = glm::vec3(
            xReverse * sizePerSection - halfSize,
            y * sizePerSection - halfSize,
            -halfSize);

         //Left.
         m_points[x + currentRow + pointsPerFace * 2] = glm::vec3(
            -halfSize,
            xReverse * sizePerSection - halfSize,
            y * sizePerSection - halfSize);

         //Right.
         m_points[x + currentRow + pointsPerFace * 3] = glm::vec3(
            halfSize,
            x * sizePerSection - halfSize,
            y * sizePerSection - halfSize);

         //Top.
         m_points[x + currentRow + pointsPerFace * 4] = glm::vec3(
            xReverse * sizePerSection - halfSize,
            halfSize,
            y * sizePerSection - halfSize);

         //Bottom.
         m_points[x + currentRow + pointsPerFace * 5] = glm::vec3(
            x * sizePerSection - halfSize,
            -halfSize,
            y * sizePerSection - halfSize);
      }
   }

   //Indices.
   int currentIndex = 0;
   for (int face = 0; face < FACE_COUNT; face++)
   {
      int faceOffset = face * pointsPerRow * pointsPerRow;

      for (int y = 0; y < sectionCount; y++)
      {
         int currentRow = y * pointsPerRow + faceOffset;

         for (int x = 0; x < sectionCount; x++)
         {
            m_indices[currentIndex + 0] = x + currentRow;
            m_indices[currentIndex + 1] = x + 1 + currentRow;
            m_indices[currentIndex + 2] = x + pointsPerRow + currentRow;

            m_indices[currentIndex + 3] = x + 1 + pointsPerRow + currentRow;
            m_indices[currentIndex + 4] = x + pointsPerRow + currentRow;
            m_indices[currentIndex + 5] = x + 1 + currentRow;

            currentIndex += 6;
         }
      }
   }

   //Spherize and generate m_normals.
   for (int i = 0; i < m_points.size(); i++)
   {
      //Create normal from origin to m_points on cube.
      m_normals[i] = glm::normalize(m_points[i] - ORIGIN);

      //Translate point along the new m_normals.
      m_points[i] = m_normals[i] * radius;
   }
}
