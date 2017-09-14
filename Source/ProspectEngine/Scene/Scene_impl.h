#pragma once
#include <memory>
#include "Terrain.h"
#include "Include/Camera.h"
#include "Include/Scene.h"
#include "Include/Entity.h"
#include "EngineDefines.h"

namespace Prospect
{
   class Scene_impl
   {
   public:
      Scene_impl(Scene& parent);

      void CreateCamera(const glm::ivec2& size);
      void CreateTerrain();

      Camera& GetCamera();
      const Camera& GetCamera() const;

      Terrain* GetTerrain();
      const Terrain* GetTerrain() const;

      Entity& CreateEntity(Mesh& mesh, Material& material);
      Entity& GetEntityAtIndex(const int index);

      std::vector<Entity>& GetEntities();

   private:
      Scene& m_parent;

      Camera m_camera;
      std::unique_ptr<Terrain> m_terrain;

      unsigned long m_nextEntityID = DEFAULT_ENTITY_ID;
      std::vector<Entity> m_entities;
   };
}
