#pragma once
#include "Renderer/Uniforms/UniformBuffer.h"
#include "Renderer/Uniforms/UniformBlocks.h"

namespace Prospect
{
   typedef UniformBuffer<CameraUniforms, 0> CameraUniformBuffer;

   struct GlobalUniformBuffers
   {
      CameraUniformBuffer Camera;
   };
}