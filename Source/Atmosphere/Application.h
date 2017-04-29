#pragma once
#include "IApplication.h"
#include "Window.h"
#include "ShaderProgram.h"

#include <glm/mat4x4.hpp>
#include <vector>
#include "Terrain.h"
#include "Atmosphere.h"
#include "CubeMap.h"

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

   glm::vec4 m_backgroundColor = { 0.0, 0.0, 0.0, 0.0 };

   glm::mat4 m_view;
   glm::mat4 m_projection;
   glm::vec3 m_sunDirection = glm::normalize(glm::vec3(-1.0, 1.0, 0));
   glm::vec3 m_earthPosition = glm::vec3(0, 0, 0);
   glm::vec3 m_eyePosition = glm::vec3(0, 0, 200.0); // glm::vec3(0, 1000.1, -100);//glm::vec3(0, 100.1, -1200.0); 

   std::unique_ptr<Terrain> m_terrain;
   std::unique_ptr<Atmosphere> m_atmosphere;
   std::unique_ptr<CubeMap> m_cubeMap;

   void UpdateViewMatrix();
};
