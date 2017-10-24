#pragma once

namespace Prospect
{
   //Responsible for holding the number of UniformBuffer binding statically.
   //This ensures all UniformBuffer bindings are unique.
   //However this means buffers cannot share the same binding point.
   class UniformBufferCounter
   {
   public:
      static GLuint Increment();
      static void Reset();

   private:
      static GLuint m_counter;
   };
}