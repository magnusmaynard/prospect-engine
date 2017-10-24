#include "ProspectEngine_pch.h"

#include "UniformBufferCounter.h"

using namespace Prospect;

GLuint UniformBufferCounter::Increment()
{
   return m_counter++;
}

void UniformBufferCounter::Reset()
{
   m_counter = 0;
}

GLuint UniformBufferCounter::m_counter = 0;
