#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>

#include "IApplication.h"
#include "Engine.h"
#include "Scene.h"
#include <vector>
#include "MeshLibrary.h"
#include "MaterialLibrary.h"

using namespace Prospect;

template class std::vector<int>;

class TestApplication : public IApplication
{
public:
   TestApplication();

   void OnStartup() override;
   void OnShutdown() override;
   void OnUpdate(double timeElapsed) override;
   void OnKeyDown(const Key& key, const KeyModifier& modifier) override;
   void OnKeyUp(const Key& key, const KeyModifier& modifier) override;
   void OnMouseMove(const glm::vec2& oldPosition, const glm::vec2& newPosition) override;

private:
   Engine m_engine;
   Scene& m_scene;
   MeshLibrary& m_meshLib;
   MaterialLibrary& m_materialLib;

   const float m_playerThreshold = 0.01;
   const float m_playerFriction = 0.25;
   const float m_playerSpeed = 0.01;
   glm::vec3 m_playerMomentum;
   bool m_playerLeft = false, m_playerRight = false, m_playerForward = false, m_playerBackward = false;
};
