#pragma once
#include <memory>
#include "Include/Camera.h"
#include "Include/Scene.h"
#include "Include/Entity.h"

#include "Libraries/EntityLibrary.h"

#include <deque>

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

      Entity& AddEntity(Mesh* mesh, Material* material);
      Entity& GetEntityAtIndex(const int index);

      //Internal
      Entity* GetRootEntity();
      Camera_impl& GetCameraImpl();
      EntityLibrary& GetEntityLib();

      void UpdateTransforms();

   private:
      Scene& m_parent;

      Camera m_camera;

      EntityLibrary m_entityLib;
      Entity* m_rootEntity;
   };
}
