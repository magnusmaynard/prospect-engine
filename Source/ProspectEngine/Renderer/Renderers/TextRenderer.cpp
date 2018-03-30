#include "ProspectEngine_pch.h"

#include "TextRenderer.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Resources/Resources.h"
#include "Resources/ResourceIO.h"

#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Scene2D/Text_impl.h"

using namespace Prospect;
using namespace glm;

TextRenderer::TextRenderer(ShaderLibrary& shaderLibrary)
   :
   m_shader(shaderLibrary.GetTextShader())
{
   m_renderDataLibrary.SetInitialise(Initialise);
   m_renderDataLibrary.SetDispose(Dispose);

   const int DEFAULT_FONT_SIZE = 12; //TODO: expose this.

   InitialiseFont(DEFAULT_FONT_SIZE);
}

void TextRenderer::InitialiseFont(const int size)
{
   auto error = FT_Init_FreeType(&m_library);
   if (error)
   {
      throw std::exception("Error initializing FreeType m_library.");
   }

   std::string fontFile = ResourceIO::GetResourcePath() + Resources::ARIAL_FONT;

   error = FT_New_Face(
      m_library,
      fontFile.c_str(),
      0,
      &m_face);

   if (error == FT_Err_Unknown_File_Format)
   {
      throw std::exception("Error: Unknown font format.");
   }
   if (error)
   {
      throw std::exception("Error: Font file could not be opened");
   }

   FT_Set_Pixel_Sizes(m_face, 0, size);
}

void TextRenderer::Initialise(TextRenderData& renderData)
{
   glCreateVertexArrays(1, &renderData.VAO);
   glCreateBuffers(renderData.BUFFER_COUNT, &renderData.Buffers[0]);

   //Positions
   glVertexArrayVertexBuffer(
      renderData.VAO,
      0,
      renderData.Buffers[renderData.BUFFER_POSITIONS],
      0,
      sizeof(vec2));

   glVertexArrayAttribFormat(
      renderData.VAO,
      0,
      2,
      GL_FLOAT,
      GL_FALSE,
      0);

   glVertexArrayAttribBinding(renderData.VAO, 0, 0);
   glEnableVertexArrayAttrib(renderData.VAO, 0);

   static const std::vector<vec2> positions(4, vec2()); //Empty data.

   glNamedBufferStorage(
      renderData.Buffers[renderData.BUFFER_POSITIONS],
      sizeof(positions[0]) * positions.size(),
      &positions[0],
      GL_DYNAMIC_STORAGE_BIT);

   //Texture coords
   glVertexArrayVertexBuffer(
      renderData.VAO,
      1,
      renderData.Buffers[renderData.BUFFER_TEXTURECOORDS],
      0,
      sizeof(vec2));

   glVertexArrayAttribFormat(
      renderData.VAO,
      1,
      2,
      GL_FLOAT,
      GL_FALSE,
      0);

   glVertexArrayAttribBinding(renderData.VAO, 1, 1);
   glEnableVertexArrayAttrib(renderData.VAO, 1);

   static const std::vector<vec2> textureCoords =
   {
      vec2(0, 0),
      vec2(0, 1),
      vec2(1, 0),
      vec2(1, 1),
   };

   glNamedBufferStorage(
      renderData.Buffers[renderData.BUFFER_TEXTURECOORDS],
      sizeof(textureCoords[0]) * textureCoords.size(),
      &textureCoords[0],
      0);
}

void TextRenderer::Dispose(TextRenderData& renderData)
{
   glDeleteVertexArrays(1, &renderData.VAO);
   glDeleteBuffers(renderData.BUFFER_COUNT, renderData.Buffers);
   glDeleteTextures(1, &renderData.Texture);
}

void TextRenderer::Render(const Text_impl& text)
{
   TextRenderData& renderData = m_renderDataLibrary.GetRenderData(text.GetId());

   if(text.IsDirty())
   {
      UpdateText(text, renderData);

      text.Clean();
   }

   glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   glDepthMask(false);

   m_shader.Bind();
   glBindVertexArray(renderData.VAO);
   glBindTexture(GL_TEXTURE_2D, renderData.Texture);

   glUniformMatrix4fv(10, 1, GL_FALSE, &text.GetTransform()[0][0]);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

   glDepthMask(true);
}

ivec2 TextRenderer::NextPowerOf2(const ivec2& value)
{
   return ivec2(NextPowerOf2(value.x), NextPowerOf2(value.y));
}

int TextRenderer::NextPowerOf2(const int value)
{
   int rval = 1;
   while (rval < value)
   {
      rval *= 2;
   }

   return rval;
}

TextBounds TextRenderer::GetTextBounds(const FT_Face face, const std::string& text)
{
   TextBounds bounds;

   FT_GlyphSlot glyph = face->glyph;
   for (unsigned int i = 0; i < text.size(); i++)
   {
      FT_Load_Char(face, text[i], FT_LOAD_RENDER);

      const auto bitmap = glyph->bitmap;

      //Set width
      //TODO: Width isn't correct.
      bounds.max.x += glyph->advance.x >> 6;

      //Set height
      const int maxHeight = glyph->bitmap_top;
      const int minHeight = maxHeight - bitmap.rows;

      bounds.max.y = max(maxHeight, bounds.max.y);
      bounds.min.y = min(minHeight, bounds.min.y);
   }

   bounds.size = ivec2(
      bounds.max.x - bounds.min.x,
      bounds.max.y - bounds.min.y);

   return bounds;
}

void TextRenderer::UpdateText(const Text_impl& text, TextRenderData& renderData)
{
   const std::string textString = text.GetText();
   const FT_GlyphSlot glyph = m_face->glyph;
   const TextBounds bounds = GetTextBounds(m_face, textString);
   const ivec2 textureSize = NextPowerOf2(bounds.size);

   glDeleteTextures(1, &renderData.Texture);
   glCreateTextures(GL_TEXTURE_2D, 1, &renderData.Texture);
   glTextureStorage2D(renderData.Texture, 1, GL_R8, textureSize.x, textureSize.y);

   glTextureParameteri(renderData.Texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTextureParameteri(renderData.Texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   std::vector<vec2> positions =
   {
      vec2(0, textureSize.y),
      vec2(0, 0),
      vec2(textureSize.x, textureSize.y),
      vec2(textureSize.x, 0),
   };

   glNamedBufferSubData(
      renderData.Buffers[renderData.BUFFER_POSITIONS],
      0,
      sizeof(positions[0]) * positions.size(),
      &positions[0]);

   int originX = 0;
   for (unsigned int i = 0; i < textString.size(); i++)
   {
      FT_Load_Char(m_face, textString[i], FT_LOAD_RENDER);

      const int width = glyph->bitmap.width;
      const int height = glyph->bitmap.rows;
      const int totalWidth = NextPowerOf2(width);
      const auto bitmap = glyph->bitmap;

      const int verticalOffset = bounds.max.y - glyph->bitmap_top;
      const int horizontalOffset = glyph->bitmap_left;

      std::vector<unsigned char> newBuffer(totalWidth * textureSize.y, 0);

      for (int y = 0; y < height; y++)
      {
         for (int x = 0; x < width; x++)
         {
            newBuffer[x + (y + verticalOffset) * totalWidth] = bitmap.buffer[x + y * width];
         }
      }

      glTextureSubImage2D(
         renderData.Texture,
         0,
         originX + horizontalOffset, 0,
         totalWidth, textureSize.y,
         GL_RED,
         GL_UNSIGNED_BYTE,
         &newBuffer[0]);

      originX += glyph->advance.x >> 6;
   }
}
