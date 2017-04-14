#pragma once
#include "Terrain.h"
#include <noise/noise.h>

using namespace noise;

Terrain::Terrain()
   :
   m_shader("terrain.vs.glsl", "terrain.fs.glsl"),
   m_origin(0, 0, 0),
   m_radius(1000.0),
   m_sectionCount(400)//benchmark=400.
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
      m_buffers[BUFFER_POINT], m_pointsSize * 3 * sizeof(float), &m_points[0], 0);
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
      m_buffers[BUFFER_INDEX], m_indicesSize * sizeof(unsigned int), &m_indices[0], 0);
   //Bind element buffer to vertex array.
   glVertexArrayElementBuffer(m_VAO, m_buffers[BUFFER_INDEX]);

   //Initialize normal buffer.
   glNamedBufferStorage(
      m_buffers[BUFFER_NORMAL], m_normalsSize * 3 * sizeof(float), &m_normals[0], 0);
   glVertexArrayVertexBuffer(m_VAO, 1, m_buffers[BUFFER_NORMAL], 0, sizeof(glm::vec3));
   glVertexArrayAttribFormat(m_VAO, 1, 3, GL_FLOAT, GL_FALSE, 0);
   glVertexArrayAttribBinding(m_VAO, 1, 1);
   glEnableVertexArrayAttrib(m_VAO, 1);
}

Terrain::~Terrain()
{
   //Delete vertex data.
   delete m_points;
   delete m_indices;
   delete m_normals;

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
   glDrawElements(GL_TRIANGLES, m_indicesSize, GL_UNSIGNED_INT, 0);

   //Unbind.
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Terrain::Transform(const glm::mat4& transform)
{
   m_transform *= transform;
}

void Terrain::GenerateSphere()
{
   static const int FACE_COUNT = 6;
   static const float SECTION_SIZE = 1.0;
   static const float SECTION_HALF_SIZE = SECTION_SIZE * 0.5;

   static const float sizePerSection = SECTION_SIZE / m_sectionCount;
   static const int pointsPerRow = m_sectionCount + 1;
   static const int pointsPerFace = pointsPerRow * pointsPerRow;
   static const int pointsPerObject = pointsPerRow * pointsPerRow * FACE_COUNT;
   static const int faceOffset0 = pointsPerFace * 0;
   static const int faceOffset1 = pointsPerFace * 1;
   static const int faceOffset2 = pointsPerFace * 2;
   static const int faceOffset3 = pointsPerFace * 3;
   static const int faceOffset4 = pointsPerFace * 4;
   static const int faceOffset5 = pointsPerFace * 5;

   //Initialize containers.
   m_pointsSize = pointsPerObject;
   m_indicesSize = pointsPerObject * 6;
   m_normalsSize = pointsPerObject;

   m_points = new glm::vec3[m_pointsSize];
   m_indices = new unsigned int[m_indicesSize];
   m_normals = new glm::vec3[m_normalsSize];

   //Points.
   int currentPointIndex = 0;
   for (int y = 0; y <= m_sectionCount; y++)
   {
      float currentY = y * sizePerSection - SECTION_HALF_SIZE;

      for (int x = 0; x <= m_sectionCount; x++)
      {
         float currentX = x * sizePerSection - SECTION_HALF_SIZE;

         //Flip m_points along y axis to make face m_normals point outwards.
         float currentXReverse = (m_sectionCount - x) * sizePerSection - SECTION_HALF_SIZE;

         //Front.
         m_points[faceOffset0 + currentPointIndex] = glm::vec3(currentX, currentY, SECTION_HALF_SIZE);

         //Back.
         m_points[faceOffset1 + currentPointIndex] = glm::vec3(currentXReverse, currentY, -SECTION_HALF_SIZE);

         //Left.
         m_points[faceOffset2 + currentPointIndex] = glm::vec3(-SECTION_HALF_SIZE, currentXReverse, currentY);

         //Right.
         m_points[faceOffset3 + currentPointIndex] = glm::vec3(SECTION_HALF_SIZE, currentX, currentY);

         //Top.
         m_points[faceOffset4 + currentPointIndex] = glm::vec3(currentXReverse, SECTION_HALF_SIZE, currentY);

         //Bottom.
         m_points[faceOffset5 + currentPointIndex] = glm::vec3(currentX, -SECTION_HALF_SIZE, currentY);

         currentPointIndex += 1;
      }
   }

   //Indices.
   int currentIndex = 0;
   for (int face = 0; face < FACE_COUNT; face++)
   {
      int faceOffset = face * pointsPerFace;

      for (int y = 0; y < m_sectionCount; y++)
      {
         int currentRow = y * pointsPerRow + faceOffset;

         for (int x = 0; x < m_sectionCount; x++)
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

   module::Perlin myModule;
   myModule.SetOctaveCount(6);
   myModule.SetFrequency(1.0);

   //Spherize and generate m_normals.
   for (int i = 0; i < m_pointsSize; i++)
   {
      //Create normal from origin to m_points on cube.
      //This is noticably faster than glm::normalize(m_points[i] - ORIGIN);
      glm::vec3 normal = m_points[i] - m_origin;
      m_normals[i] = normal / sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

      //Calculate random elevation with Perlin noise.
      glm::vec3 elevation = m_normals[i] * static_cast<float>(myModule.GetValue(m_points[i].x, m_points[i].y, m_points[i].z)) * 10.0f;

      //Translate point along the new m_normals.
      m_points[i] = m_normals[i] * m_radius + elevation;
   }
}
