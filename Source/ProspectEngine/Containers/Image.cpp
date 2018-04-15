#include "ProspectEngine_pch.h"

#include "Include/Image.h"

using namespace Prospect;

Image::Image()
   :
   Width(0),
   Height(0),
   Channels(0)
{
}

Image::Image(int width, int height, const std::vector<float>& data)
   :
   Width(width),
   Height(height),
   Channels(1),
   Data(data)
{
}

Image::Image(int width, int height, int channels, const std::vector<float>& data)
   :
   Width(width),
   Height(height),
   Channels(channels),
   Data(data)
{
}

Image::Image(
   int width,
   int height,
   int channels,
   const std::vector<unsigned char>& data)
   :
   Width(width),
   Height(height),
   Channels(channels),
   DataB(data)
{
}
