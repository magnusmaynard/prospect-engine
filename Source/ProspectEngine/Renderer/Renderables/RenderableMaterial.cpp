#include "RenderableMaterial.h"
#include <algorithm>

using namespace Prospect;

RenderableMaterial::RenderableMaterial(Material& material)
   :
   m_material(material)
{
}

RenderableMaterial::~RenderableMaterial()
{
}

RenderableMaterial::RenderableMaterial(RenderableMaterial&& other)
   :
   m_material(other.m_material)
{
}

void RenderableMaterial::Use()
{
   auto& diffuse = m_material.GetDiffuse();
   float diffuseRGBA[4] = { diffuse.R, diffuse.G, diffuse.B, diffuse.A };

   glUniform4fv(3, 1, diffuseRGBA);
}