#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>

#include <vector>

#include "IApplication.h"
#include "Engine.h"
#include "Scene.h"
#include "MeshLibrary.h"
#include "MaterialLibrary.h"
#include "Player.h"

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
   Player m_player;
};
