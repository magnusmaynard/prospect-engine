#include "ProspectEngine_pch.h"

#include "Resources/ResourceIO.h"

#include <windows.h>
#include <fstream> 
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Prospect;

std::string ResourceIO::m_resourcePath;

std::string ResourceIO::GetResourcePath()
{
   if(m_resourcePath.empty())
   {
      char path[2048];
      GetModuleFileNameA(nullptr, path, 2048);
      m_resourcePath = std::string(path) + "\\..\\Resources\\";
   }

   return m_resourcePath;
}

std::string ResourceIO::ReadText(const std::string& fileName)
{
   std::string filePath = GetResourcePath() + fileName;

   std::ifstream sourceFile(filePath);
   std::stringstream sourceStream;
   sourceStream << sourceFile.rdbuf();

   return sourceStream.str();
}

Bitmap ResourceIO::ReadBitmap(const std::string& fileName)
{
   std::string filePath = GetResourcePath() + fileName;

   int width = 0;
   int height = 0;
   int channels = 0;
   float* rawData = stbi_loadf(filePath.c_str(), &width, &height, &channels, 1);

   std::vector<float> data(rawData, rawData + width * height);

   return Bitmap(width, height, channels, data);
}