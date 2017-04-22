#pragma once

#include <string>
#include <memory>

#include "VertexShader.h"
#include "TessEvaluationShader.h"
#include "TessControlShader.h"
#include "GeometryShader.h"
#include "FragmentShader.h"

class ShaderProgram
{
public:
   ShaderProgram();
   ~ShaderProgram();

   void Add(const VertexShader& vertexShader);
   void Add(const TessControlShader& tessControlShader);
   void Add(const TessEvaluationShader& tessEvaluationShader);
   void Add(const GeometryShader& geometryShader);
   void Add(const FragmentShader& fragmentShader);

   bool Compile();

   void Use() const;
   GLint GetUniformLocation(const std::string& uniform) const;

private:
   GLuint m_program = -1;

   std::unique_ptr<BaseShader> m_vertexShader;
   std::unique_ptr<BaseShader> m_tessControlShader;
   std::unique_ptr<BaseShader> m_tessEvaluationShader;
   std::unique_ptr<BaseShader> m_geometryShader;
   std::unique_ptr<BaseShader> m_fragmentShader;

   static bool ShaderProgram::CompileAndAttachShader(
      const GLuint program,
      const std::unique_ptr<BaseShader>& shader);

   static bool LinkProgram(const GLuint& program);
};
