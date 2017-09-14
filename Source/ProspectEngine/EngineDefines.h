#pragma once
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <string>
#include "Include/Material.h"

namespace Prospect
{
   static const int DEFAULT_WIDTH = 600;
   static const int DEFAULT_HEIGHT = 400;
   static const glm::ivec2 DEFAULT_CAMERA_SIZE(DEFAULT_WIDTH, DEFAULT_HEIGHT);

   static const unsigned long DEFAULT_ENTITY_ID = 0;
   static const unsigned long DEFAULT_MESH_ID = 0;
   static const unsigned long DEFAULT_MATERIAL_ID = 0;

   static const Color DEFAULT_COLOR(1, 1, 0);

   const glm::vec3 POS_X(1, 0, 0);
   const glm::vec3 POS_Y(0, 1, 0);
   const glm::vec3 POS_Z(0, 0, 1);
   const glm::vec3 NEG_X(-1, 0, 0);
   const glm::vec3 NEG_Y(0, -1, 0);
   const glm::vec3 NEG_Z(0, 0, -1);

   const glm::vec3 DEFAULT_TRANSLATION(0, 0, 0);
   const glm::vec3 DEFAULT_ROTATION(0, 0, 0);
   const glm::vec3 DEFAULT_SCALE(1, 1, 1);

   static const int MAX_MATERIALS = 100;
   static const int MAX_MESHES = 100;
   static const int MAX_ENTITIES = 100;
}