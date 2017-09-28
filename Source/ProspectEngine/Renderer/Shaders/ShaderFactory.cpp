#include "ShaderFactory.h"
#include <algorithm>

using namespace Prospect;

Shader& ShaderFactory::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
   Shader newShader;
   newShader.AddVertexShader(vertexShader);
   newShader.AddFragmentShader(fragmentShader);

   return AddShaderIfDoesNotExist(newShader);
}

Shader& ShaderFactory::AddShaderIfDoesNotExist(Shader& newShader)
{
   auto it = std::find_if(m_shaders.begin(), m_shaders.end(), [&](Shader& existingShader)
   {
      return newShader == existingShader;
   });

   if (it != m_shaders.end())
   {
      return *it;
   }
   else
   {
      newShader.Compile();

      m_shaders.push_back(std::move(newShader));

      return m_shaders.back();
   }
}
