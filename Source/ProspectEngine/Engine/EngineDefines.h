#pragma once

#include "Include/Material.h"
#include "Include/Color.h"

namespace Prospect
{
   static const double TIME_PER_UPDATE = 1000.0 / 60.0;

   static const int DEFAULT_WIDTH = 600;
   static const int DEFAULT_HEIGHT = 400;
   static const unsigned long NULL_ID = 0;

   static const glm::vec3 POS_X(1, 0, 0);
   static const glm::vec3 POS_Y(0, 1, 0);
   static const glm::vec3 POS_Z(0, 0, 1);
   static const glm::vec3 NEG_X(-1, 0, 0);
   static const glm::vec3 NEG_Y(0, -1, 0);
   static const glm::vec3 NEG_Z(0, 0, -1);

   static const glm::vec3 DEFAULT_TRANSLATION(0, 0, 0);
   static const glm::vec3 DEFAULT_ROTATION(0, 0, 0);
   static const glm::vec3 DEFAULT_SCALE(1, 1, 1);

   static const glm::ivec2 DEFAULT_CAMERA_SIZE(DEFAULT_WIDTH, DEFAULT_HEIGHT);
   static const float DEFAULT_CAMERA_NEAR = 0.01f;
   static const float DEFAULT_CAMERA_FAR = 10000.f;
   static const float DEFAULT_CAMERA_FOV = 45.f;
   static const float DEFAULT_CAMERA_MIN_ANGLE = 20.f;
   static const float DEFAULT_CAMERA_MAX_ANGLE = 160.f;
   static const float DEFAULT_CAMERA_SENSITIVITY = 0.2f;

   static const Color DEFAULT_LIGHT_COLOR(1, 1, 1);
   static const float DEFAULT_LIGHT_BRIGHTNESS = 1.f;

   static const glm::vec3 DEFAULT_ATMOSPHERE_SUN_DIRECTION(1, 1, -1);
   static const float DEFAULT_ATMOSPHERE_INNER_RADIUS = 1500.f;
   static const float DEFAULT_ATMOSPHERE_OUTTER_RADIUS = 2000.f;
   static const float DEFAULT_ATMOSPHERE_DENSITY_SCALE = 0.25f;
   static const float DEFAULT_ATMOSPHERE_ALTITUDE = 1500.1f;
}