#pragma once
#include <string>

namespace Prospect
{
   class Resources
   {
   public:
      static std::string GetResourcePath();
      static std::string GetShaderPath();
      static std::string GetTexturePath();

   private:
      static std::string m_resourcePath;
   };
}
