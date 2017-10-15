#include "ProspectEngine_pch.h"

#include "Renderer/Bitmap.h"

using namespace Prospect;


Bitmap::Bitmap(int width, int height, int channels, const std::vector<float>& data)
   :
   Width(width),
   Height(height),
   Channels(channels),
   Data(data)
{
}
