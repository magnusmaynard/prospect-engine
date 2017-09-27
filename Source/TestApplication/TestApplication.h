#pragma once

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
   void OnUpdate(const unsigned int time) override;
   void OnKeyDown(const Key& key, const KeyModifier& modifier) override;
   void OnKeyUp(const Key& key, const KeyModifier& modifier) override;
   void OnMouseMove(const glm::vec2& oldPosition, const glm::vec2& newPosition) override;

private:
   Engine m_engine;
   Scene& m_scene;
   MeshLibrary& m_meshLib;
   MaterialLibrary& m_materialLib;
};
