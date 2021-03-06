#include "ProspectEngine_pch.h"

#include "Include/Terrain.h"
#include "Scene/Terrain/Terrain_impl.h"

using namespace Prospect;

Terrain::Terrain(
   const glm::vec3& origin,
   const Bitmap& heightMap,
   float size,
   float minHeight,
   float maxHeight)
   :
   m_impl(std::make_shared<Terrain_impl>(
      origin,
      heightMap,
      size,
      minHeight,
      maxHeight))
{
}

Terrain::Terrain(std::shared_ptr<Terrain_impl>& impl)
   :
   m_impl(impl)
{
}

Terrain::~Terrain() = default;

void Terrain::SetGroundTexture(const Bitmap& groundTexture)
{
   m_impl->SetGroundTexture(groundTexture);
}
