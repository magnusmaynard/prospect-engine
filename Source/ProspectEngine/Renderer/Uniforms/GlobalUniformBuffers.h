#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"

namespace Prospect
{
   typedef UniformBuffer<CameraUniforms> CameraUniformBuffer;
   typedef UniformBuffer<DirectionalLightListUniforms> DirectionalLightListUniformBuffer;
   typedef UniformBuffer<MaterialLibraryUniforms> MaterialLibraryUniformBuffer;

   struct GlobalUniformBuffers
   {
      CameraUniformBuffer Camera = CameraUniformBuffer("CameraUniforms");
      DirectionalLightListUniformBuffer DirectionalLights = DirectionalLightListUniformBuffer("DirectionalLightListUniforms");
      MaterialLibraryUniformBuffer MaterialLibrary = MaterialLibraryUniformBuffer("MaterialLibraryUniforms");
   };
}