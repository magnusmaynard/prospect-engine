#include "Resources.h"

#include <windows.h>

using namespace Prospect;

std::string Resources::m_resourcePath;

std::string Resources::GetResourcePath()
{
   if(m_resourcePath.empty())
   {
      char path[2048];
      GetModuleFileNameA(nullptr, path, 2048);
      m_resourcePath = std::string(path) + "\\..\\Resources\\";
   }

   return m_resourcePath;
}

std::string Resources::GetShaderPath()
{
   return GetResourcePath() + "Shaders\\";
}

std::string Resources::GetTexturePath()
{
   return GetResourcePath() + "Textures\\";
}

std::string Resources::GetFontPath()
{
   return GetResourcePath() + "Fonts\\";
}