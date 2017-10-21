#include "ProspectEngine_pch.h"

#include "Include/Bitmap.h"

using namespace Prospect;

Bitmap::Bitmap(int width, int height, const std::vector<float>& data)
   :
   Width(width),
   Height(height),
   Channels(1),
   Data(data)
{
}

Bitmap::Bitmap(int width, int height, int channels, const std::vector<float>& data)
   :
   Width(width),
   Height(height),
   Channels(channels),
   Data(data)
{
}
