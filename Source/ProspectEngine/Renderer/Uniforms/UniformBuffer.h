#pragma once

#include "Renderer/Shaders/Shader.h"

namespace Prospect
{
   template <typename T, GLuint I>
   class UniformBuffer
   {
   public:
      UniformBuffer()
         :
         m_buffer(0),
         m_blockIndex(I),
         m_bindingIndex(I)
      {
         glCreateBuffers(1, &m_buffer);
         glBindBufferBase(GL_UNIFORM_BUFFER, m_bindingIndex, m_buffer);
      }

      void Bind(const Shader& shader) const
      {
         glValidateProgram(shader.GetProgram());
         GLint result;
         glGetProgramiv(shader.GetProgram(), GL_VALIDATE_STATUS, &result);
         bool isValid = GL_TRUE == result;

         GLuint blockIndex = glGetUniformBlockIndex(shader.GetProgram(), "NodeUniforms"); //TODO: temp

         glUniformBlockBinding(shader.GetProgram(), m_blockIndex, m_bindingIndex);
      }

      void Update(T block)
      {
         m_block = block;

         glNamedBufferData(m_buffer, sizeof(T), &m_block, GL_DYNAMIC_DRAW);
      }

   private:
      T m_block;

      GLuint m_buffer;
      GLuint m_blockIndex;
      GLuint m_bindingIndex;
   };
}
