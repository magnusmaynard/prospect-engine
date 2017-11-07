#pragma once

namespace Prospect
{
   //Do not use vec3/mat3 as the memory does not align with Uniforms blocks in std140 layout:
   //https://stackoverflow.com/a/38172697/3209889

   struct CameraUniforms
   {
      CameraUniforms()
      {
      }

      CameraUniforms(
         const glm::mat4& projection,
         const glm::mat4& view,
         const glm::vec3 position,
         const glm::vec2 screenSize)
         :
         Projection(projection),
         View(view),
         Position(glm::vec4(position, 0)),
         ScreenSize(screenSize)
      {
      }

      glm::mat4 Projection;
      glm::mat4 View;
      glm::vec4 Position;
      glm::vec2 ScreenSize;
   };

   struct NodeUniforms
   {
      NodeUniforms()
      {
      }

      NodeUniforms(
         const glm::vec3& origin,
         const glm::ivec4& edges,
         const float size,
         const float level)
         :
         Origin(glm::vec4(origin, 0)),
         Edges(edges),
         Size(size),
         Level(level)
      {
      }

      glm::vec4 Origin;
      glm::ivec4 Edges;
      float Size = 0;
      float Level = 0;
   };

   struct DirectionalLightUniforms
   {
      DirectionalLightUniforms()
      {
      }

      DirectionalLightUniforms(
         glm::vec3 direction)
         :
         Direction(glm::vec4(direction, 0))
      {
      }

      glm::vec4 Direction;
   };

   struct AtmosphereUniforms
   {
      float Altitude;
   };
}