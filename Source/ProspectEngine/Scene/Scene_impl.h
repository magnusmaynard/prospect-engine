#pragma once
#include <memory>
#include "Terrain.h"
#include "Include/Camera.h"
#include "Include/Scene.h"
#include "Include/Entity.h"
#include "EngineDefines.h"

namespace Prospect
{
   class Camera_impl;

   class Scene_impl
   {
   public:
      Scene_impl(Scene& parent);

      //Public
      Camera& GetCamera();
      const Camera& GetCamera() const;

      Entity& CreateEntity(Mesh& mesh, Material& material);
      Entity& GetEntityAtIndex(const int index);

      //Internal
      std::vector<Entity>& GetEntities();
      Camera_impl& GetCameraImpl();

   private:
      Scene& m_parent;

      Camera m_camera;

      unsigned long m_nextEntityID = DEFAULT_ENTITY_ID;
      std::vector<Entity> m_entities;
   };
}
