#include "Application.h"

#include <glm/vec4.hpp>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp> 
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/normal.hpp>

void GenerateCube(std::vector<glm::vec3>& points, std::vector<unsigned int>& indices, std::vector<glm::vec3>& normals)
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

   points.resize(pointsPerObject);
   indices.resize(pointsPerObject * 6);
   normals.resize(pointsPerObject);

   //Points.
   for (int y = 0; y <= sectionCount; y++)
   {
      int currentRow = y * pointsPerRow;

      for (int x = 0; x <= sectionCount; x++)
      {
         //Flip points along y axis to make face normals point outwards.
         int xReverse = (sectionCount - x);

         //Front.
         points[x + currentRow + pointsPerFace * 0] = glm::vec3(
            x * sizePerSection - halfSize,
            y * sizePerSection - halfSize,
            halfSize);

         //Back.
         points[x + currentRow + pointsPerFace * 1] = glm::vec3(
            xReverse * sizePerSection - halfSize,
            y * sizePerSection - halfSize,
            -halfSize);

         //Left.
         points[x + currentRow + pointsPerFace * 2] = glm::vec3(
            -halfSize,
            xReverse * sizePerSection - halfSize,
            y * sizePerSection - halfSize);

         //Right.
         points[x + currentRow + pointsPerFace * 3] = glm::vec3(
            halfSize,
            x * sizePerSection - halfSize,
            y * sizePerSection - halfSize);

         //Top.
         points[x + currentRow + pointsPerFace * 4] = glm::vec3(
            xReverse * sizePerSection - halfSize,
            halfSize,
            y * sizePerSection - halfSize);

         //Bottom.
         points[x + currentRow + pointsPerFace * 5] = glm::vec3(
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
            indices[currentIndex + 0] = x + currentRow;
            indices[currentIndex + 1] = x + 1 + currentRow;
            indices[currentIndex + 2] = x + pointsPerRow + currentRow;

            indices[currentIndex + 3] = x + 1 + pointsPerRow + currentRow;
            indices[currentIndex + 4] = x + pointsPerRow + currentRow;
            indices[currentIndex + 5] = x + 1 + currentRow;

            currentIndex += 6;
         }
      }
   }

   //Spherize and generate normals.
   for (int i = 0; i < points.size(); i++)
   {
      //Create normal from origin to points on cube.
      normals[i] = glm::normalize(points[i] - ORIGIN);

      //Translate point along the new normals.
      points[i] = normals[i] * radius;
   }
}

//void GenerateSphere2(std::vector<glm::vec3>& points, std::vector<unsigned int>& indices)
//{
//   points = {
//      glm::vec3(0.0f, -1.0f, 0.0f),
//      glm::vec3(1.0f, 0.0f, 0.0f),
//      glm::vec3(0.0f, 0.0f, 1.0f),
//      glm::vec3(-1.0f, 0.0f, 0.0f),
//      glm::vec3(0.0f, 0.0f, -1.0f),
//      glm::vec3(0.0f, 1.0f, 0.0f)
//   };
//
//   indices = {
//      0, 1, 2,
//      0, 2, 3,
//      0, 3, 4,
//      0, 4, 1,
//      1, 5, 2,
//      2, 5, 3,
//      3, 5, 4,
//      4, 5, 1
//   };
//}

//TODO: This constructor never gets passed window init because of render loop. Remove it somehow?
Application::Application()
   :
   m_window(this)
{
   m_window.Open();
}

void Application::Startup()
{
   //Enable shaders to overlay and blend colors.
   glBlendFunc(GL_SRC_ALPHA, GL_ONE); //GL_ONE_MINUS_SRC_ALPHA
   glEnable(GL_BLEND);

   glCullFace(GL_BACK);
   glEnable(GL_CULL_FACE);

   m_skyboxShader = std::make_unique<ShaderProgram>("skybox.vs.glsl", "skybox.fs.glsl");
   m_skyboxSunDirectionLocation = m_skyboxShader->GetUniformLocation("sunDirection");
   m_skyboxTimeLocation = m_skyboxShader->GetUniformLocation("time");
   m_skyboxViewLocation = m_skyboxShader->GetUniformLocation("view");
   m_skyboxProjectionLocation = m_skyboxShader->GetUniformLocation("projection");
   m_skyboxResolutionLocation = m_skyboxShader->GetUniformLocation("resolution");
   m_skyboxEyePositionLocation = m_skyboxShader->GetUniformLocation("eyePosition");
   m_skyboxEarthPositionLocation = m_skyboxShader->GetUniformLocation("earthPosition");

   //View.
   auto up = glm::vec3(0, 1, 0);
   //m_view = glm::lookAt(m_eyePosition, glm::vec3(0, 0, 0), up);
   m_view = glm::lookAt(m_eyePosition, m_eyePosition + glm::vec3(0, 0, 1), up);

   //Projection.
   float aspect = m_window.GetSize().x / m_window.GetSize().y;
   m_projection = glm::perspective(65.0f, aspect, 0.0001f, 1000.0f); //55

   //Create earth
   std::vector<glm::vec3> points;
   std::vector<unsigned int> indices;
   std::vector<glm::vec3> normals;
   GenerateCube(points, indices, normals);

   m_earth = std::make_unique<Object3D>(points, indices, normals);
}

void Application::Shutdown()
{
}

void Application::Render(const double time)
{
   //m_eyePosition.z = -1.0 - sin(time);
  
   //m_view = glm::translate(m_view, glm::vec3(0,0,sin(time*2.0) * 0.01));


   //Clear
   glClearBufferfv(GL_COLOR, 0, &m_backgroundColor[0]);

   //Earth
   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   //m_earth->Transform(glm::rotate(glm::mat4(), 0.01f, glm::vec3(0, 1, 0)));
   m_earth->Draw(m_view, m_projection, m_sunDirection);

   //Skybox
  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   m_skyboxShader->Use();

   glUniform3fv(m_skyboxSunDirectionLocation, 1, &m_sunDirection[0]);
   glUniform1f(m_skyboxTimeLocation, static_cast<float>(time));
   glUniformMatrix4fv(m_skyboxViewLocation, 1, GL_FALSE, &m_view[0][0]);
   glUniformMatrix4fv(m_skyboxProjectionLocation, 1, GL_FALSE, &m_projection[0][0]);
   glUniform2fv(m_skyboxResolutionLocation, 1, &m_window.GetSize()[0]);
   glUniform3fv(m_skyboxEyePositionLocation, 1, &m_eyePosition[0]);
   glUniform3fv(m_skyboxEarthPositionLocation, 1, &m_earthPosition[0]);

   glDrawArrays(GL_TRIANGLES, 0, 6);
}


void Application::OnKeyPressed(int key, int action, int mods)
{
   const float rotationIncrement = 0.02f;
   if (key == 49) //1
   {
      m_sunDirection = glm::rotateX(m_sunDirection, -rotationIncrement);
   }

   if (key == 50) //2
   {
      m_sunDirection = glm::rotateX(m_sunDirection, rotationIncrement);
   }

   std::cout << glm::to_string(m_sunDirection) << std::endl;
}