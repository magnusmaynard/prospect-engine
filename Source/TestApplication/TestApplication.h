#pragma once

#include "IApplication.h"
#include "Engine.h"
#include "Scene.h"
#include <vector>

using namespace Prospect;

template class EXPORT_DLL std::vector<int>;

class TestApplication : public IApplication
{
public:
   TestApplication();

   void OnStartup() override;
   void OnShutdown() override;
   void OnUpdate(const unsigned int time) override;
   void OnKeyDown(const Key& key, const KeyModifier& modifier) override;

private:
   Engine m_engine;
   Scene& m_scene;
   MeshLibrary& m_meshLib;

   //Terrain* m_terrain = nullptr;
};
