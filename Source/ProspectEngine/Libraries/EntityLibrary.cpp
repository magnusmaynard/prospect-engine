#include "ProspectEngine_pch.h"

#include "EntityLibrary.h"

using namespace Prospect;
using namespace glm;

EntityLibrary::EntityLibrary()
   :
   m_nextEntityID(NULL_ID)
{
}

Entity& EntityLibrary::operator[] (int index)
{
   return m_entities[index];
}

int EntityLibrary::Count() const
{
   return m_entities.size();
}

Entity& EntityLibrary::AddEntity(Entity* parent, Mesh* mesh, Material* material)
{
   m_nextEntityID++;

   m_entities.emplace_back(Entity(*this, m_nextEntityID, parent, mesh, material));

   return m_entities.back();
}