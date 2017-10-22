#pragma once

namespace Prospect
{
   //Responsible for holding the number of UniformBuffer binding statically.
   //This ensures all UniformBuffer bindings are unique.
   //However this means buffers cannot share the same binding point.
   class UniformBufferBindingsCounter
   {
   public:
      static GLuint Increment();
   private:
      static GLuint m_bindingsCounter;
   };
}