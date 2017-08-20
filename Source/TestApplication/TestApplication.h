#pragma once

#include "IApplication.h"
#include "Engine.h"
#include "Scene.h"

using namespace Prospect;

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
   //std::unique_ptr<Scene> m_scene;

   //Terrain* m_terrain = nullptr;
};
