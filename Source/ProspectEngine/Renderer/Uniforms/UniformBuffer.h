#pragma once

#include "Renderer/Shaders/Shader.h"
#include "Renderer/Uniforms/UniformBufferBindingsCounter.h"

namespace Prospect
{
   template <typename T>
   class UniformBuffer
   {
   public:
      //Create a UniformBuffer at a defined index.
      //This is used for global UniformBuffers, as they have a known block index.
      UniformBuffer(GLuint index)
         :
         m_buffer(0),
         m_blockIndex(index),
         m_bindingIndex(index)
      {
         CreateBuffer();
      }

      ////Create a UniformBuffer at the index found in a Shader.
      ////This is used for shader specific UniformBuffers, which do not have a known block index.
      //UniformBuffer(const Shader& shader, const std::string& uniformBlockName)
      //   :
      //   m_buffer(0),
      //   m_blockIndex(0),
      //   m_bindingIndex(m_bindingsCounter.Increment())
      //{
      //   GLuint index = glGetUniformBlockIndex(shader.GetProgram(), uniformBlockName.c_str());

      //   if (index == GL_INVALID_INDEX)
      //   {
      //      std::cerr << "Error: Cannot find '" << uniformBlockName <<
      //         "' uniform block in program " << shader.GetProgram() << std::endl;
      //   }
      //   else if (index == GL_INVALID_OPERATION)
      //   {
      //      std::cerr << "Error: Invalid program " << shader.GetProgram() << std::endl;
      //   }
      //   else
      //   {
      //      //Success.
      //      m_blockIndex = index;

      //      CreateBuffer();
      //   }
      //}

      //Bind the UniformBuffer to a specific shader.
      //This only needs to be called once per shader.
      void Bind(const Shader& shader) const
      {
         glUniformBlockBinding(shader.GetProgram(), m_blockIndex, m_bindingIndex);
      }

      //Updates buffer with new data.
      void Update(T block)
      {
         m_block = block;

         glNamedBufferData(m_buffer, sizeof(T), &m_block, GL_DYNAMIC_DRAW);
      }

   private:
      //Constructs a buffer at the binding index.
      void CreateBuffer()
      {
         glCreateBuffers(1, &m_buffer);
         glBindBufferBase(GL_UNIFORM_BUFFER, m_bindingIndex, m_buffer);
      }

      T m_block;

      GLuint m_buffer;
      GLuint m_blockIndex;
      GLuint m_bindingIndex;

      //This ensures all UniformBuffer bindings are unique.
      //However this means buffers cannot share the same binding point.
      UniformBufferBindingsCounter m_bindingsCounter;
   };
}
