#include "ProspectEngine_pch.h"

#include "Include/Utilities/IO.h"
#include "Include/Bitmap.h"

#include <windows.h>
#include <fstream> 
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ObjReader.h"

using namespace Prospect;
using namespace glm;

std::string IO::GetExecutablePath()
{
   char buffer[MAX_PATH];
   GetModuleFileNameA(nullptr, buffer, MAX_PATH);

   const auto position = std::string(buffer).find_last_of("\\/");
   return std::string(buffer).substr(0, position + 1);
}

std::string IO::ReadText(const std::string& filePath)
{
   std::ifstream sourceFile(filePath);

   if (!sourceFile)
   {
      std::cerr << "Error: Unable to read file at path: " << filePath << std::endl;
      return "";
   }

   std::stringstream sourceStream;
   sourceStream << sourceFile.rdbuf();

   return sourceStream.str();
}

Bitmap IO::ReadBitmap(const std::string& filePath, const bool monochrome)
{
   const int desiredChannels = monochrome ? 1 : 3;

   int width = 0;
   int height = 0;
   int channels = 0;
   float* rawData = stbi_loadf(filePath.c_str(), &width, &height, &channels, desiredChannels);

   const std::vector<float> data(rawData, rawData + width * height * desiredChannels);
   return Bitmap(width, height, channels, data);
}

bool IO::ReadObj(Mesh& mesh, const std::string& filename)
{
   return ObjReader::Read(mesh, filename);
}