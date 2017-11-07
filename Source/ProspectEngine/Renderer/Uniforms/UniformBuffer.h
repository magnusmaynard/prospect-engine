#pragma once

#include "Renderer/Shaders/Shader.h"
#include "Renderer/Uniforms/UniformBufferCounter.h"

namespace Prospect
{
   template <typename T>
   class UniformBuffer
   {
   public:
      UniformBuffer(const std::string& name)
         :
         m_buffer(0),
         m_bindingIndex(UniformBufferCounter::Increment()),
         m_name(name)
      {
         glCreateBuffers(1, &m_buffer);
         glBindBufferBase(GL_UNIFORM_BUFFER, m_bindingIndex, m_buffer);
      }

      ~UniformBuffer()
      {
         glDeleteBuffers(1, &m_buffer);
      }

      void Bind(const Shader& shader) const
      {
         GLuint blockIndex = glGetUniformBlockIndex(shader.GetProgram(), m_name.c_str());

         if (blockIndex == GL_INVALID_INDEX)
         {
            std::cerr << "Error: Cannot find '" << m_name <<
               "' uniform block in program " << shader.GetProgram() << std::endl;
         }
         else if (blockIndex == GL_INVALID_OPERATION)
         {
            std::cerr << "Error: Invalid program " << shader.GetProgram() << std::endl;
         }
         else
         {
            //Success.
            glUniformBlockBinding(shader.GetProgram(), blockIndex, m_bindingIndex);
         }
      }

      //Updates buffer with new data.
      void Update(const T& block)
      {
         glNamedBufferData(m_buffer, sizeof(T), &block, GL_DYNAMIC_DRAW);
      }

   private:
      GLuint m_buffer;
      GLuint m_bindingIndex;

      std::string m_name;
   };
}
