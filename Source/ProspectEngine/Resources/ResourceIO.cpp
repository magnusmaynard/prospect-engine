#include "ProspectEngine_pch.h"

#include "Include/Utilities/IO.h"
#include "Resources/ResourceIO.h"

using namespace Prospect;

std::string ResourceIO::m_resourcePath;

std::string ResourceIO::GetResourcePath()
{
   if(m_resourcePath.empty())
   {
      m_resourcePath = IO::GetExecutablePath() + "Resources\\";
   }

   return m_resourcePath;
}

std::string ResourceIO::ReadText(const std::string& resourceName)
{
   return IO::ReadText(GetResourcePath() + resourceName);
}

Bitmap ResourceIO::ReadBitmap(const std::string& resourceName)
{
   return IO::ReadBitmap(GetResourcePath() + resourceName);
}