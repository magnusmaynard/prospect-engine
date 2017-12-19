#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"

namespace Prospect
{
   typedef UniformBuffer<CameraUniforms> CameraUniformBuffer;
   typedef UniformBuffer<LightsUniforms> LightsUniformBuffer;
   typedef UniformBuffer<MaterialLibraryUniforms> MaterialLibraryUniformBuffer;

   struct GlobalUniformBuffers
   {
      CameraUniformBuffer Camera = CameraUniformBuffer("CameraUniforms");
      LightsUniformBuffer Lights = LightsUniformBuffer("LightsUniforms");
      MaterialLibraryUniformBuffer MaterialLibrary = MaterialLibraryUniformBuffer("MaterialLibraryUniforms");
   };
}