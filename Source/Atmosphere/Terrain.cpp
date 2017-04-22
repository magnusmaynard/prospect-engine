#pragma once
#include "Terrain.h"
#include <noise/noise.h>
#include "TessControlShader.h"
#include "TessEvaluationShader.h"

using namespace noise;

Terrain::Terrain()
   :
   m_origin(0, 0, 0),
   m_radius(1000.0),
   m_sectionCount(1)//benchmark=400.
{
   m_shader.Add(VertexShader("terrain"));
   m_shader.Add(TessControlShader("terrain"));
   m_shader.Add(TessEvaluationShader("terrain"));
   m_shader.Add(FragmentShader("terrain"));
   m_shader.Compile();

   GeneratePlane();

   m_modelLocation = m_shader.GetUniformLocation("model");
   m_viewLocation = m_shader.GetUniformLocation("view");
   m_projectionLocation = m_shader.GetUniformLocation("projection");
   //m_sunDirectionLocation = m_shader.GetUniformLocation("sunDirection");

   glCreateVertexArrays(1, &m_VAO);
   glBindVertexArray(m_VAO);

   glCreateBuffers(BUFFER_COUNT, m_buffers);

   //Initialize point buffer.
   glNamedBufferStorage(
      m_buffers[BUFFER_POINT], m_pointsSize * 3 * sizeof(float), &m_points[0], 0);
   //Bind vertex buffer to vertex array.
   glVertexArrayVertexBuffer(m_VAO, 0, m_buffers[BUFFER_POINT], 0, sizeof(glm::vec3));
   //Specify the format of the atrribute.
   glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
   //Specify which vertex buffer binding to use for the attribute.
   glVertexArrayAttribBinding(m_VAO, 0, 0);
   //Enable attribute.
   glEnableVertexArrayAttrib(m_VAO, 0);

   ////Initialize index buffer.
   //glNamedBufferStorage(
   //   m_buffers[BUFFER_INDEX], m_indicesSize * sizeof(unsigned int), &m_indices[0], 0);
   ////Bind element buffer to vertex array.
   //glVertexArrayElementBuffer(m_VAO, m_buffers[BUFFER_INDEX]);

   ////Initialize normal buffer.
   //glNamedBufferStorage(
   //   m_buffers[BUFFER_NORMAL], m_normalsSize * 3 * sizeof(float), &m_normals[0], 0);
   //glVertexArrayVertexBuffer(m_VAO, 1, m_buffers[BUFFER_NORMAL], 0, sizeof(glm::vec3));
   //glVertexArrayAttribFormat(m_VAO, 1, 3, GL_FLOAT, GL_FALSE, 0);
   //glVertexArrayAttribBinding(m_VAO, 1, 1);
   //glEnableVertexArrayAttrib(m_VAO, 1);
}

Terrain::~Terrain()
{
   //Delete vertex data.
   delete m_points;

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

   //Draw.
   glPatchParameteri(GL_PATCH_VERTICES, 4);
   glDrawArrays(GL_PATCHES, 0, m_pointsSize);

   //Unbind.
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Terrain::Transform(const glm::mat4& transform)
{
   m_transform *= transform;
}

void Terrain::GeneratePlane()
{
   static const int FACE_COUNT = 1;
   static const float SECTION_SIZE = 1000.0;
   static const float SECTION_HALF_SIZE = SECTION_SIZE * 0.5;

   static const float sizePerSection = SECTION_SIZE / m_sectionCount;
   static const int pointsPerRow = m_sectionCount + 1;
   static const int pointsPerFace = pointsPerRow * pointsPerRow;

   //Initialize containers.
   m_pointsSize = pointsPerFace;

   m_points = new glm::vec3[m_pointsSize];

   //Points.
   int currentPointIndex = 0;
   for (int y = 0; y <= m_sectionCount; y++)
   {
      float currentY = y * sizePerSection - SECTION_HALF_SIZE;

      for (int x = 0; x <= m_sectionCount; x++)
      {
         float currentX = x * sizePerSection - SECTION_HALF_SIZE;

         //Front.
         m_points[currentPointIndex] = glm::vec3(currentX, currentY, 0);

         currentPointIndex += 1;
      }
   }

   ////Indices.
   //int currentIndex = 0;
   //for (int face = 0; face < FACE_COUNT; face++)
   //{
   //   int faceOffset = face * pointsPerFace;

   //   for (int y = 0; y < m_sectionCount; y++)
   //   {
   //      int currentRow = y * pointsPerRow + faceOffset;

   //      for (int x = 0; x < m_sectionCount; x++)
   //      {
   //         m_indices[currentIndex + 0] = x + currentRow;
   //         m_indices[currentIndex + 1] = x + 1 + currentRow;
   //         m_indices[currentIndex + 2] = x + pointsPerRow + currentRow;

   //         m_indices[currentIndex + 3] = x + 1 + pointsPerRow + currentRow;
   //         m_indices[currentIndex + 4] = x + pointsPerRow + currentRow;
   //         m_indices[currentIndex + 5] = x + 1 + currentRow;

   //         currentIndex += 6;
   //      }
   //   }
   //}

   //module::Perlin myModule;
   //myModule.SetOctaveCount(6);
   //myModule.SetFrequency(1.0);

   ////Spherize and generate m_normals.
   //for (int i = 0; i < m_pointsSize; i++)
   //{
   //   //Create normal from origin to m_points on cube.
   //   //This is noticably faster than glm::normalize(m_points[i] - ORIGIN);
   //   glm::vec3 normal = m_points[i] - m_origin;
   //   m_normals[i] = normal / sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

   //   //Calculate random elevation with Perlin noise.
   //   glm::vec3 elevation = m_normals[i] * static_cast<float>(myModule.GetValue(m_points[i].x, m_points[i].y, m_points[i].z)) * 10.0f;

   //   //Translate point along the new m_normals.
   //   m_points[i] = m_normals[i] * m_radius + elevation;
   //}
}
