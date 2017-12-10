#pragma once
#include "Scene/Lights/Light_impl.h"
#include "Scene/Material_impl.h"
#include "Scene/Camera_impl.h"
#include "Scene/Atmosphere_impl.h"
#include "Engine/EngineDefines.h"
#include "Libraries/MaterialLibrary_impl.h"

namespace Prospect
{
   //Do not use vec3/mat3 as the memory does not align with Uniforms blocks in std140 layout:
   //https://stackoverflow.com/a/38172697/3209889

   struct CameraUniforms
   {
      CameraUniforms()
      {
      }

      CameraUniforms(const Camera_impl& camera)
         :
         PerspectiveProjection(camera.GetPerspectiveProjection()),
         OrthographicProjection(camera.GetOrthographicProjection()),
         View(camera.GetView()),
         ViewDirection(glm::vec4(camera.GetForward(), 0)),
         Position(glm::vec4(camera.GetPosition(), 0)),
         ScreenSize(camera.GetSize())
      {
      }

      glm::mat4 PerspectiveProjection;
      glm::mat4 OrthographicProjection;
      glm::mat4 View;
      glm::vec4 ViewDirection;
      glm::vec4 Position;
      glm::vec2 ScreenSize;
   };

   struct DirectionalLightUniforms
   {
      DirectionalLightUniforms()
      {
      }

      DirectionalLightUniforms(const Light_impl& directionalLight)
         :
         Direction({ normalize(directionalLight.GetDirection()), 0 }),
         DiffuseColor(directionalLight.GetColor().ToRGBA()),
         Brightness({ directionalLight.GetBrightness(), 0, 0, 0 })
      {
      }

      glm::vec4 Direction;
      glm::vec4 DiffuseColor;
      glm::vec4 Brightness;
   };

   //struct LightsUniforms
   //{
   //   DirectionalLightUniforms Lights[10];
   //};

   struct MaterialsUniforms
   {
      struct MaterialUniforms
      {
         MaterialUniforms()
         {
         }

         MaterialUniforms(const Material_impl& material)
            :
            Diffuse(material.GetDiffuse().ToRGBA()),
            Ambient(material.GetAmbient().ToRGBA()),
            SpecularAndPower(material.GetSpecular().ToRGB(), material.GetSpecularPower())
         {
         }

         glm::vec4 Diffuse;
         glm::vec4 Ambient;
         glm::vec4 SpecularAndPower;
      };

      MaterialsUniforms()
      {
      }

      MaterialsUniforms(const MaterialLibrary_impl& materials)
      {
         for(int i = 0; i < materials.GetMaterialCount(); i++)
         {
            Materials[i] = MaterialUniforms(materials.GetMaterialImpl(i));
         }
      }

      MaterialUniforms Materials[MAX_MATERIALS];
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
         const int level)
         :
         Origin(glm::vec4(origin, 0)),
         Edges(edges),
         Size(size),
         Level(static_cast<float>(level))
      {
      }

      glm::vec4 Origin;
      glm::ivec4 Edges;
      float Size = 0;
      float Level = 0;
   };

   struct ScatteringUniforms
   {
      ScatteringUniforms()
      {
      }

      ScatteringUniforms(const Atmosphere_impl& atmosphere)
         :
         SunDirection(glm::vec4(normalize(atmosphere.GetSunDirection()), 0)),
         InnerRadius(atmosphere.GetInnerRadius()),
         OutterRadius(atmosphere.GetOutterRadius()),
         DensityScale(atmosphere.GetDensityScale()),
         Altitude(atmosphere.GetAltitude())
      {
      }

      glm::vec4 SunDirection;
      float InnerRadius;
      float OutterRadius;
      float DensityScale;
      float Altitude;
   };

   struct ModelUniforms
   {
      glm::mat4 Model;
   };

   struct SunUniforms
   {
      glm::mat4 Model;
   };

   struct TextUniforms
   {
      glm::mat4 Model;
   };
}
