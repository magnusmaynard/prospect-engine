#pragma once

#include <string>

namespace Prospect
{
   struct Bitmap;

   class IO
   {
   public:
      static std::string GetExecutablePath();

      static std::string ReadText(const std::string& filename);
      static Bitmap ReadBitmap(const std::string& filename);
   };
}
