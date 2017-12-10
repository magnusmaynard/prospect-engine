#include "ProspectEngine_pch.h"

#include "ShaderFactory.h"
#include "Resources/Resources.h"

using namespace Prospect;

std::deque<Shader> ShaderFactory::m_shaders;

Shader& ShaderFactory::CreateBlinnPhongShader()
{
   return CreateShader(
      Resources::BLINNPHONG_VERTEX_SHADER,
      Resources::BLINNPHONG_FRAGMENT_SHADER);
}

Shader& ShaderFactory::CreateShader(
   const std::string& vertexShader,
   const std::string& fragmentShader)
{
   Shader newShader;
   newShader.AddVertexShader(vertexShader);
   newShader.AddFragmentShader(fragmentShader);

   return AddShaderIfUnique(newShader);
}

Shader& ShaderFactory::CreateShader(
   const std::string& vertexShader,
   const std::string& tessControlShader,
   const std::string& tessEvaluationShader,
   const std::string& fragmentShader)
{
   Shader newShader;
   newShader.AddVertexShader(vertexShader);
   newShader.AddTessControlShader(tessControlShader);
   newShader.AddTessEvaluationShader(tessEvaluationShader);
   newShader.AddFragmentShader(fragmentShader);

   return AddShaderIfUnique(newShader);
}

Shader& ShaderFactory::AddShaderIfUnique(Shader& newShader)
{
   auto it = std::find_if(m_shaders.begin(), m_shaders.end(), [&](Shader& existingShader)
   {
      return newShader == existingShader;
   });


   if (it != m_shaders.end())
   {
      //Shader already exists.
      return *it;
   }

   newShader.Compile();

   m_shaders.push_back(std::move(newShader));
   return m_shaders.back();
}
