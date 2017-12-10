#include "ProspectEngine_pch.h"

#include "Include/Utilities/IO.h"
#include "Include/Bitmap.h"

#include <windows.h>
#include <fstream> 
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Prospect;

std::string IO::GetExecutablePath()
{
   char buffer[MAX_PATH];
   GetModuleFileNameA(nullptr, buffer, MAX_PATH);

   auto position = std::string(buffer).find_last_of("\\/");
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

Bitmap IO::ReadBitmap(const std::string& filePath)
{
   int width = 0;
   int height = 0;
   int channels = 0;
   float* rawData = stbi_loadf(filePath.c_str(), &width, &height, &channels, 1);

   const std::vector<float> data(rawData, rawData + width * height);

   return Bitmap(width, height, channels, data);
}