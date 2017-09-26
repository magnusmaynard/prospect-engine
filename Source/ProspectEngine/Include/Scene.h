#pragma once

#include <memory>

namespace Prospect
{
   class Scene_impl;

   class Mesh;
   class Material;
   class Entity;
   class Camera;

   class Scene
   {
   public:
      //Public
      ~Scene();

      Entity& AddEntity(Mesh* mesh, Material* material);
      Entity& GetEntity(const int index);

      const Camera& GetCamera() const;
      Camera& GetCamera();

      //Internal
      Scene();

   private:
      std::unique_ptr<Scene_impl> m_impl;

      friend class Engine_impl;
   };
}