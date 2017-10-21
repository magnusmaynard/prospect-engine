#pragma once

namespace Prospect
{
   struct Bitmap
   {
      Bitmap(int width, int height, const std::vector<float>& data);
      Bitmap(int width, int height, int channels, const std::vector<float>& data);

      const int Width;
      const int Height;
      const int Channels;
      const std::vector<float> Data;
   };
}