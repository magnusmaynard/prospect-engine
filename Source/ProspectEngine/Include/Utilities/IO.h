#pragma once

#include <string>

namespace Prospect
{
   struct Image;
   class Mesh;

   class IO
   {
   public:
      static std::string GetExecutablePath();

      static std::string ReadText(const std::string& filename);

      static Image ReadBitmap(const std::string& filename, const bool monochrome = false);

      static bool ReadObj(Mesh& mesh, const std::string& filename);

      static void WritePNG(const std::string& filename, const Image& image);
   };
}
