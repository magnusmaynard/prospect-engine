#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Renderer/Pipeline/Shaders/Shader.h"

#include "Renderer/Pipeline/Shaders/TextShader.h"
#include "Renderer/Renderers/RenderData.h"
#include "Renderer/Renderers/RenderDataLibrary.h"

namespace Prospect
{
   class Text_impl;
   class ShaderLibrary;
   struct GlobalUniformBuffers;

   //Relative to origin baseline.
   struct TextBounds
   {
      glm::ivec2 min;
      glm::ivec2 max;
      glm::ivec2 size;
   };

   struct TextRenderData : RenderData
   {
      const enum Buffers
      {
         BUFFER_POSITIONS,
         BUFFER_TEXTURECOORDS,
         BUFFER_COUNT
      };

      GLuint Texture;
      GLuint VAO;
      GLuint Buffers[BUFFER_COUNT];
   };

   class TextRenderer
   {
   public:
      TextRenderer(ShaderLibrary& shaderLibrary);
      void Render(const Text_impl& text);

   private:
      static void Initialise(TextRenderData& renderData);
      static void Dispose(TextRenderData& renderData);

      void InitialiseFont(int size);
      void UpdateText(const Text_impl& text, TextRenderData& renderData);

      static TextBounds GetTextBounds(const FT_Face face, const std::string& text);
      static glm::ivec2 NextPowerOf2(const glm::ivec2& value);
      static int NextPowerOf2(const int value);

      FT_Library m_library;
      FT_Face m_face;

      TextShader& m_shader;

      RenderDataLibrary<TextRenderData> m_renderDataLibrary;
   };
}
