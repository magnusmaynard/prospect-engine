#pragma once
#include "Shaders/ShaderProgram.h"
#include "Scene/Entity_impl.h"

namespace Prospect
{
   class RenderableEntity
   {
   public:
      RenderableEntity(Entity_impl& entity);

   //private:
      Entity_impl& m_entity;

      //ShaderProgram m_program;
   };
}
