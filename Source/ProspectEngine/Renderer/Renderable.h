#pragma once
#include "Shaders/ShaderProgram.h"
#include "Scene/Entity_impl.h"

namespace Prospect
{
   class Scene_impl;

   class Renderable
   {
   public:
      Renderable(Entity_impl& entity);
      ~Renderable();
      Renderable(const Renderable& other) = delete;
      Renderable& operator=(const Renderable &) = delete;
      Renderable(Renderable&& other);
      Renderable& operator=(Renderable&& other);

      void Render(Scene_impl& scene);

   private:
      void UpdateVertexData();

      Entity_impl* m_entity;
      ShaderProgram m_program;
      GLuint m_VAO;

      enum BUFFERS
      {
         BUFFER_VERTICES,
         BUFFER_INDICES,
         BUFFER_COUNT,
      };

      GLuint m_buffers[BUFFER_COUNT];
   };
}
