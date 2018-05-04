#pragma once

#include "Include/Material.h"
#include "Include/Color.h"

namespace Prospect
{
   namespace Defaults
   {
      static const std::string TITLE = "";
      static const int WIDTH = 600;
      static const int HEIGHT = 400;

      static const glm::vec3 TRANSLATION(0, 0, 0);
      static const glm::vec3 ROTATION(0, 0, 0);
      static const glm::vec3 SCALE(1, 1, 1);

      static const glm::ivec2 CAMERA_SIZE(WIDTH, HEIGHT);
      static const float CAMERA_NEAR = 0.01f;
      static const float CAMERA_FAR = 1000.f;
      static const float CAMERA_FOV = 45.f;
      static const float CAMERA_MIN_ANGLE = 10.f;
      static const float CAMERA_MAX_ANGLE = 170.f;
      static const float CAMERA_SENSITIVITY = 0.2f;

      static const Color LIGHT_COLOR(1, 1, 1);
      static const float LIGHT_BRIGHTNESS = 0.8f;
      static const float LIGHT_RANGE = 100.f;
      static const float LIGHT_ANGLE = 45.f;
      static const bool LIGHT_CAST_SHADOWS = true;
      static const std::vector<float> LIGHT_SHADOW_CASCADES = { 0.02f, 0.05f, 0.1f, 0.2f }; //{ 0.33f, 0.66f, 1.0f };// 

      static const float ATMOSPHERE_INNER_RADIUS = 1500.f;
      static const float ATMOSPHERE_OUTTER_RADIUS = 2000.f;
      static const float ATMOSPHERE_DENSITY_SCALE = 0.25f;
      static const float ATMOSPHERE_ALTITUDE = 1500.1f;
      static const glm::vec3 ATMOSPHERE_SUN_DIRECTION = glm::vec3(0, -1, 1);

      static const Color MATERIAL_DIFFUSE(0.15f, 0.53f, 0.86f);
      static const Color MATERIAL_EMISSIVE(0.f, 0.f, 0.f);
      static const Color MATERIAL_SPECULAR(0.3f, 0.3f, 0.3f);
      static const int MATERIAL_SPECULAR_POWER = 16;

      static const int FONT_SIZE = 12;
   }

   namespace Defines
   {
      static const double TIME_PER_UPDATE = 1000.0 / 60.0;
      static const unsigned long NULL_ID = 0;

      static const glm::vec3 POS_X(1, 0, 0);
      static const glm::vec3 POS_Y(0, 1, 0);
      static const glm::vec3 POS_Z(0, 0, 1);
      static const glm::vec3 NEG_X(-1, 0, 0);
      static const glm::vec3 NEG_Y(0, -1, 0);
      static const glm::vec3 NEG_Z(0, 0, -1);

      static const int INVALID_SHADOW_MAP_ID = -1;

      static const int MAX_MATERIALS = 10;
      static const int MAX_DIRECTIONAL_LIGHTS = 10;
      static const int MAX_SHADOW_MAPS = 10;
   }
}