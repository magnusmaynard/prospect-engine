#pragma once
#include "ProspectEngine.h"

using namespace glm;

class TestApplication
{
public:
   TestApplication();

   void Startup();
   void Shutdown();
   void Update(unsigned int time);
   void KeyDown(const Keys& keys);

private:
   ProspectEngine m_pe;

   Terrain* m_terrain = nullptr;
};
