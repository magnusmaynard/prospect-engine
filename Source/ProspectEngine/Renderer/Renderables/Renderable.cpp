#include "ProspectEngine_pch.h"

#include "Renderable.h"

using namespace Prospect;

unsigned Renderable::m_nextId = 0;

Renderable::Renderable()
   :
   m_id(m_nextId++),
   m_isDirty(true)
{
}

unsigned Renderable::GetId() const
{
   return m_id;
}

bool Renderable::IsDirty() const
{
   return m_isDirty;
}

bool Renderable::Clean() const
{
   m_isDirty = false;
   return m_isDirty;
}
