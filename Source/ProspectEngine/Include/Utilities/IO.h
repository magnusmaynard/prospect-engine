#pragma once

#include <string>

namespace Prospect
{
   struct Bitmap;
   class Mesh;

   class IO
   {
   public:
      static std::string GetExecutablePath();

      static std::string ReadText(const std::string& filename);

      static Bitmap ReadBitmap(const std::string& filename, const bool monochrome = false);

      static bool ReadObj(Mesh& mesh, const std::string& filename);
   };
}
