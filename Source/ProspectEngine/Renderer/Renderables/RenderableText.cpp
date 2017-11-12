#include "ProspectEngine_pch.h"

#include "RenderableText.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Resources/Resources.h"
#include "Renderer/Shaders/ShaderFactory.h"
#include "Resources/Resources.h"
#include "Resources/ResourceIO.h"

#include "Renderer/Uniforms/GlobalUniformBuffers.h"

using namespace Prospect;
using namespace glm;

RenderableText::RenderableText(
   const GlobalUniformBuffers& globalUniformBuffers,
   const std::string& text,
   const glm::ivec2& position,
   int size)
   :
   m_shader(ShaderFactory::CreateShader(Resources::TEXT_VERTEX_SHADER, Resources::TEXT_FRAGMENT_SHADER)),
   m_text(text),
   m_position(position),
   m_textIsDirty(true),
   m_transformIsDirty(true),
   m_textUniformBuffer("TextUniforms")
{
   globalUniformBuffers.Camera.Bind(m_shader);
   m_textUniformBuffer.Bind(m_shader);

   InitialiseFont(size);

   CreateBuffers();
}

void RenderableText::InitialiseFont(int size)
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

void RenderableText::CreateBuffers()
{
   glCreateVertexArrays(1, &m_VAO);
   glCreateBuffers(BUFFER_COUNT, &m_buffers[0]);

   //Positions
   glVertexArrayVertexBuffer(
      m_VAO,
      0,
      m_buffers[BUFFER_POSITIONS],
      0,
      sizeof(vec2));

   glVertexArrayAttribFormat(
      m_VAO,
      0,
      2,
      GL_FLOAT,
      GL_FALSE,
      0);
   glVertexArrayAttribBinding(m_VAO, 0, 0);
   glEnableVertexArrayAttrib(m_VAO, 0);

   static const std::vector<vec2> positions(4, vec2()); //Empty data.

   glNamedBufferStorage(
      m_buffers[BUFFER_POSITIONS],
      sizeof(positions[0]) * positions.size(),
      &positions[0],
      GL_DYNAMIC_STORAGE_BIT);

   //Texture coords
   glVertexArrayVertexBuffer(
      m_VAO,
      1,
      m_buffers[BUFFER_TEXTURECOORDS],
      0,
      sizeof(vec2));

   glVertexArrayAttribFormat(
      m_VAO,
      1,
      2,
      GL_FLOAT,
      GL_FALSE,
      0);

   glVertexArrayAttribBinding(m_VAO, 1, 1);
   glEnableVertexArrayAttrib(m_VAO, 1);

   static const std::vector<vec2> textureCoords =
   {
      vec2(0, 1),
      vec2(0, 0),
      vec2(1, 1),
      vec2(1, 0)
   };

   glNamedBufferStorage(
      m_buffers[BUFFER_TEXTURECOORDS],
      sizeof(textureCoords[0]) * textureCoords.size(),
      &textureCoords[0],
      0);
}

void RenderableText::SetText(const std::string& text)
{
   if (m_text != text)
   {
      m_text = text;

      m_textIsDirty = true;
   }
}

void RenderableText::SetPosition(const ivec2 position)
{
   if (m_position != position)
   {
      m_position = position;

      m_transformIsDirty = true;
   }
}

void RenderableText::Render()
{
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   UpdateText();
   UpdateTransform();

   m_shader.Bind();
   glBindVertexArray(m_VAO);
   glBindTexture(GL_TEXTURE_2D, m_texture);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

ivec2 RenderableText::NextPowerOf2(const ivec2& value)
{
   return ivec2(NextPowerOf2(value.x), NextPowerOf2(value.y));
}

int RenderableText::NextPowerOf2(int value)
{
   int rval = 1;
   while (rval < value)
   {
      rval *= 2;
   }

   return rval;
}

TextBounds RenderableText::GetTextBounds(const FT_Face face, const std::string& text)
{
   TextBounds bounds;

   FT_GlyphSlot glyph = face->glyph;
   for (unsigned int i = 0; i < text.size(); i++)
   {
      FT_Load_Char(face, text[i], FT_LOAD_RENDER);
   
      auto bitmap = glyph->bitmap;
   
      //Set width
      //TODO: Width isn't correct.
      bounds.max.x += glyph->advance.x >> 6;
   
      //Set height
      int maxHeight = glyph->bitmap_top;
      int minHeight = maxHeight - bitmap.rows;

      bounds.max.y = max(maxHeight, bounds.max.y);
      bounds.min.y = min(minHeight, bounds.min.y);
   }

   bounds.size = ivec2(
      bounds.max.x - bounds.min.x,
      bounds.max.y - bounds.min.y);

   return bounds;
}

void RenderableText::UpdateText()
{
   if (!m_textIsDirty)
   {
      return;
   }

   m_textIsDirty = false;

   FT_GlyphSlot glyph = m_face->glyph;

   TextBounds bounds = GetTextBounds(m_face, m_text);
   ivec2 textureSize = NextPowerOf2(bounds.size);

   glDeleteTextures(1, &m_texture);
   glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);
   glTextureStorage2D(m_texture, 1, GL_R8, textureSize.x, textureSize.y);

   glTextureParameteri(m_texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTextureParameteri(m_texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   std::vector<vec2> positions =
   {
      vec2(0, 0),
      vec2(0, textureSize.y),
      vec2(textureSize.x, 0),
      vec2(textureSize.x, textureSize.y)
   };

   glNamedBufferSubData(
      m_buffers[BUFFER_POSITIONS],
      0,
      sizeof(positions[0]) * positions.size(),
      &positions[0]);

   int originX = 0;
   for (unsigned int i = 0; i < m_text.size(); i++)
   {
      FT_Load_Char(m_face, m_text[i], FT_LOAD_RENDER);

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
         m_texture,
         0,
         originX + horizontalOffset, 0,
         totalWidth, textureSize.y,
         GL_RED,
         GL_UNSIGNED_BYTE,
         &newBuffer[0]);

      originX += glyph->advance.x >> 6;
   }
}

void RenderableText::UpdateTransform()
{
   if (!m_transformIsDirty)
   {
      return;
   }

   m_transformIsDirty = false;

   m_transform = translate(mat4(), vec3(m_position.x, m_position.y, 10));

   m_textUniformBuffer.Update(TextUniforms{
      m_transform
   });
}
