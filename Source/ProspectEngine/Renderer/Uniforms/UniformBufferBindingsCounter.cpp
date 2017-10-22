#include "ProspectEngine_pch.h"

#include "UniformBufferBindingsCounter.h"

using namespace Prospect;

GLuint UniformBufferBindingsCounter::Increment()
{
   return m_bindingsCounter++;
}

GLuint UniformBufferBindingsCounter::m_bindingsCounter = 10;
