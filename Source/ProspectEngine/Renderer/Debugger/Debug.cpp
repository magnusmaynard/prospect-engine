#include "ProspectEngine_pch.h"

#include "Debug.h"

using namespace Prospect;

void Debug::CheckErrors()
{
#ifdef _DEBUG
   GLenum error;
   while ((error = glGetError()) != GL_NO_ERROR)
   {
      std::cerr << "Error: 0x" << std::hex << error << std::endl;
   };
#endif
}
