#pragma once

#include "EngineDefines.h"
#include "Include/Entity.h"
#include <deque>

namespace Prospect
{
   class EntityLibrary
   {
   public:
      EntityLibrary();
      Entity& AddEntity(Entity* parent, Mesh* mesh, Material* material);
      Entity& operator[] (int index);
      int Count() const;

      unsigned long m_nextEntityID = NULL_ID;
      std::deque<Entity> m_entities;
   };
}
