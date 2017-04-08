#pragma once
#include "IApplication.h"
#include "Window.h"
#include "ShaderProgram.h"

#include <glm/mat4x4.hpp>
#include <vector>
#include "Object3D.h"

class Application : public IApplication
{
public:
   Application();

   void Startup() override;
   void Shutdown() override;
   void Render(const double time) override;

   void OnKeyPressed(int key, int action, int mods) override;

private:
   Window m_window;
   std::unique_ptr<ShaderProgram> m_skyboxShader;

   GLint m_skyboxSunDirectionLocation = 0;
   GLint m_skyboxTimeLocation = 0;
   GLint m_skyboxViewLocation = 0;
   GLint m_skyboxProjectionLocation = 0;
   GLint m_skyboxResolutionLocation = 0;
   GLint m_skyboxEyePositionLocation = 0;
   GLint m_skyboxEarthPositionLocation = 0;

   glm::vec3 m_earthPosition = glm::vec3(0, 0, 0);
   glm::vec3 m_eyePosition = glm::vec3(0, 1000.1, 0);//glm::vec3(0, 0.50, -1.8); //glm::vec3(0, 0, -1.8);// glm::vec3(0, 1, 3);
   glm::mat4 m_view;
   glm::mat4 m_projection;

   std::unique_ptr<Object3D> m_earth;
   glm::vec3 m_sunDirection = glm::vec3(0, -0.5, -0.5);

   glm::vec4 m_backgroundColor = { 0.0, 0.0, 0.0, 0.0 };
};
