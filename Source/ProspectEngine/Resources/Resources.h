#pragma once
#include <string>

namespace Resources
{
   namespace Shaders
   {
      static const std::string QUAD_VERTEX = "Shaders/Quad.vs.glsl";
      static const std::string LIGHTING_FRAGMENT = "Shaders/Lighting.fs.glsl";
      static const std::string ATMOSPHERE_FRAGMENT = "Shaders/Atmosphere.fs.glsl";
      static const std::string GODRAYS_FRAGMENT = "Shaders/GodRays.fs.glsl";

      static const std::string SHADOWMAP_VERTEX = "Shaders/ShadowMap.vs.glsl";
      static const std::string SHADOWMAP_FRAGMENT = "Shaders/ShadowMap.fs.glsl";

      static const std::string SIMPLE_VERTEX = "Shaders/Simple.vs.glsl";
      static const std::string SIMPLE_FRAGMENT = "Shaders/Simple.fs.glsl";
      static const std::string BLINNPHONG_VERTEX = "Shaders/BlinnPhong.vs.glsl";
      static const std::string BLINNPHONG_FRAGMENT = "Shaders/BlinnPhong.fs.glsl";
      static const std::string TEXT_VERTEX = "Shaders/Text.vs.glsl";
      static const std::string TEXT_FRAGMENT = "Shaders/Text.fs.glsl";
      static const std::string TERRAIN_VERTEX = "Shaders/Terrain.vs.glsl";
      static const std::string TERRAIN_TESSCONTROL = "Shaders/Terrain.tcs.glsl";
      static const std::string TERRAIN_TESSEVALUATION = "Shaders/Terrain.tes.glsl";
      static const std::string TERRAIN_FRAGMENT = "Shaders/Terrain.fs.glsl";
      static const std::string SUN_VERTEX = "Shaders/Sun.vs.glsl";
      static const std::string SUN_FRAGMENT = "Shaders/Sun.fs.glsl";
      static const std::string GRASS_VERTEX = "Shaders/Grass.vs.glsl";
      static const std::string GRASS_GEOMETRY = "Shaders/Grass.gs.glsl";
      static const std::string GRASS_FRAGMENT = "Shaders/Grass.fs.glsl";

      static const std::string DEBUG_VERTEX = "Shaders/Debug.vs.glsl";
      static const std::string DEBUG_FRAGMENT = "Shaders/Debug.fs.glsl";
   }

   namespace Fonts
   {
      static const std::string ARIAL_FONT = "Fonts/arial.ttf";
   }
}