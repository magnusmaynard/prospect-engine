#pragma once

namespace Prospect
{
   struct Image
   {
      Image();
      Image(int width, int height, const std::vector<float>& data);
      Image(int width, int height, int channels, const std::vector<float>& data);
      Image(int width, int height, int channels, const std::vector<unsigned char>& data);

      const int Width;
      const int Height;
      const int Channels;
      const std::vector<float> Data;
      const std::vector<unsigned char> DataB;
   };
}