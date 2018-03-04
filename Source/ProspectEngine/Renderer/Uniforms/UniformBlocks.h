#pragma once
#include "Scene/Lights/DirectionalLight_impl.h"
#include "Scene/Material_impl.h"
#include "Scene/Camera_impl.h"
#include "Scene/Atmosphere_impl.h"
#include "Scene/Entity_impl.h"
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
         InversePerspectiveProjection(inverse(camera.GetPerspectiveProjection())),
         OrthographicProjection(camera.GetOrthographicProjection()),
         View(camera.GetView()),
         Position(glm::vec4(camera.GetPosition(), 0)),
         ScreenSize(camera.GetSize())
      {
      }

      glm::mat4 PerspectiveProjection;
      glm::mat4 InversePerspectiveProjection;
      glm::mat4 OrthographicProjection;
      glm::mat4 View;
      glm::vec4 Position;
      glm::vec2 ScreenSize;
   };

   //struct LightUniforms
   //{
   //   LightUniforms()
   //   {
   //   }

   //   LightUniforms(const Light_impl& light)
   //      :
   //      Position(light.GetPosition(), 0),
   //      Direction({ normalize(light.GetDirection()), 0 }),
   //      ColorAndBrightness(light.GetColor().ToRGB(), light.GetBrightness()),
   //      RangeAndAngleAndType(light.GetRange(), light.GetAngle(), light.GetType(), 0)
   //   {
   //   }

   //   glm::vec4 Position;
   //   glm::vec4 Direction;
   //   glm::vec4 ColorAndBrightness;
   //   glm::vec4 RangeAndAngleAndType;
   //};

   //struct LightsUniforms
   //{
   //   LightsUniforms(const std::vector<const Light_impl*>& lights)
   //      :
   //      Count(lights.size())
   //   {
   //      for (size_t i = 0; i < lights.size(); i++)
   //      {
   //         Lights[i] = LightUniforms(*lights[i]);
   //      }
   //   }

   //   std::array<LightUniforms, MAX_LIGHTS> Lights;
   //   int Count;
   //};

   struct DirectionalLightUniforms
   {
      DirectionalLightUniforms()
      {
      }

      DirectionalLightUniforms(const DirectionalLight_impl& light)
         :
         Position(light.GetPosition(), 0),
         Direction({ normalize(light.GetDirection()), 0 }),
         ColorAndBrightness(light.GetColor().ToRGB(), light.GetBrightness()),
         ShadowMapIndex(light.GetShadowMapIndex(), 0, 0 ,0)
      {
      }

      glm::vec4 Position;
      glm::vec4 Direction;
      glm::vec4 ColorAndBrightness;
      glm::vec4 ShadowMapIndex;
   };

   struct DirectionalLightListUniforms
   {
      DirectionalLightListUniforms(const std::vector<const DirectionalLight_impl*>& lights)
         :
         Count(lights.size(), 0)
      {
         for (size_t i = 0; i < lights.size(); i++)
         {
            Lights[i] = DirectionalLightUniforms(*lights[i]);
         }
      }

      std::array<DirectionalLightUniforms, MAX_DIRECTIONAL_LIGHTS> Lights;
      glm::vec2 Count;
   };

   struct MaterialLibraryUniforms
   {
      struct MaterialUniforms
      {
         MaterialUniforms()
         {
         }

         MaterialUniforms(const Material_impl& material)
            :
            Diffuse(material.GetDiffuse().ToRGBA()),
            Ambient(material.GetEmissive().ToRGBA()),
            SpecularAndPower(material.GetSpecular().ToRGB(), material.GetSpecularPower())
         {
         }

         glm::vec4 Diffuse;
         glm::vec4 Ambient;
         glm::vec4 SpecularAndPower;
      };

      MaterialLibraryUniforms(const MaterialLibrary_impl& materials)
      {
         for(int i = 0; i < materials.GetMaterialCount(); i++)
         {
            Materials[i] = MaterialUniforms(materials.GetMaterialImpl(i));
         }
      }

      std::array<MaterialUniforms, MAX_MATERIALS> Materials;
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

   struct AtmosphereUniforms
   {
      AtmosphereUniforms(const Atmosphere_impl& atmosphere)
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

   struct EntityUniforms
   {
      EntityUniforms(const Entity_impl& entity)
         :
         Model(entity.GetTransformMatrix()),
         Normal(entity.GetNormalMatrix()),
         MaterialID(entity.GetMaterialID(), 0, 0, 0)
      {
      }

      glm::mat4 Model;
      glm::mat4 Normal;
      glm::ivec4 MaterialID;
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
