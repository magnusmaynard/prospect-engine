#pragma once
#include "Engine.h"
#include "IApplication.h"

using namespace glm;
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
   Prospect::Engine m_engine;

   Terrain* m_terrain = nullptr;
};
