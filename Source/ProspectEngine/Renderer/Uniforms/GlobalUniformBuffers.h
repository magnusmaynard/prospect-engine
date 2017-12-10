#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"

namespace Prospect
{
   typedef UniformBuffer<CameraUniforms> CameraUniformBuffer;
   typedef UniformBuffer<DirectionalLightUniforms> DirectionalLightUniformBuffer;
   typedef UniformBuffer<MaterialsUniforms> MaterialsUniformBuffer;

   struct GlobalUniformBuffers
   {
      CameraUniformBuffer Camera = CameraUniformBuffer("CameraUniforms");
      DirectionalLightUniformBuffer DirectionalLight = DirectionalLightUniformBuffer("DirectionalLightUniforms");
      MaterialsUniformBuffer Materials = MaterialsUniformBuffer("MaterialUniforms");
   };
}