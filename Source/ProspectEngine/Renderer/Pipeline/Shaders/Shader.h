#pragma once

#include "Renderer/Pipeline/ShaderStages/ShaderStage.h"

namespace Prospect
{
   class Shader
   {
   public:
      Shader(
         const std::string& vertexShader,
         const std::string& fragmentShader);

      Shader(
         const std::string& vertexShader,
         const std::string& tessControlShader,
         const std::string& tessEvaluationShader,
         const std::string& fragmentShader);

      ~Shader();

      bool operator ==(const Shader &other) const;

      void Bind() const;
      GLint GetUniformLocation(const std::string& uniform) const;
      GLuint GetProgram() const;

   protected:
      bool Compile();

   private:
      void AddVertexShader(const std::string& shaderName);
      void AddTessControlShader(const std::string& shaderName);
      void AddTessEvaluationShader(const std::string& shaderName);
      void AddGeometryShader(const std::string& shaderName);
      void AddFragmentShader(const std::string& shaderName);

      bool AreEqual(ShaderStage* lhs, ShaderStage* rhs) const;

      static bool Shader::CompileAndAttachShader(
         const GLuint program,
         const std::unique_ptr<ShaderStage>& shader);

      static bool LinkProgram(const GLuint program);
      static bool ValidateProgram(const GLuint program);

      GLuint m_program;

      std::unique_ptr<ShaderStage> m_vertexShader;
      std::unique_ptr<ShaderStage> m_tessControlShader;
      std::unique_ptr<ShaderStage> m_tessEvaluationShader;
      std::unique_ptr<ShaderStage> m_geometryShader;
      std::unique_ptr<ShaderStage> m_fragmentShader;

      friend class ShaderFactory;
   };
}
