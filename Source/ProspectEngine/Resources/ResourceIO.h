#pragma once
#include <string>
#include "Include/Bitmap.h"

namespace Prospect
{
   class ResourceIO
   {
   public:
      static std::string GetResourcePath();

      static std::string ReadText(const std::string& filename);
      static Bitmap ReadBitmap(const std::string& filename);

   private:
      static std::string m_resourcePath;
   };
}
