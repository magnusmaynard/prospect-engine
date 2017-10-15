#include "ProspectEngine_pch.h"

#include "Text.h"

#include <ft2build.h>
#include FT_FREETYPE_H

//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include <stb_image_write.h>

#include "Renderer/Shaders/ShaderFactory.h"
#include "Renderer/Shaders/Shaders.h"
#include "Resources/Resources.h"

using namespace Prospect;
using namespace glm;

Text::Text(const std::string& text, const glm::ivec2& position, int size)
   :
   m_text(text),
   m_position(position),
   m_shader(ShaderFactory::CreateShader(TEXT_VERTEX_SHADER, TEXT_FRAGMENT_SHADER)),
   m_textIsDirty(true),
   m_transformIsDirty(true)
{
   InitialiseFont(size);

   CreateBuffers();
}

void Text::InitialiseFont(int size)
{
   auto error = FT_Init_FreeType(&m_library);
   if (error)
   {
      throw std::exception("Error initializing FreeType m_library.");
   }

   std::string fontFile = Resources::GetFontPath() + "arial.ttf";

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

void Text::CreateBuffers()
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

void Text::SetText(const std::string& text)
{
   m_text = text;

   m_textIsDirty = true;
}

void Text::SetPosition(const glm::ivec2 position)
{
   m_position = position;

   m_transformIsDirty = true;
}

void Text::Render(const ivec2& screenSize)
{
   if(m_textIsDirty)
   {
      m_textIsDirty = false;

      UpdateText();
   }

   UpdateProjectionMatrix(screenSize);
   UpdateTransformMatrix();

   m_shader.Bind();
   glBindVertexArray(m_VAO);
   glBindTexture(GL_TEXTURE_2D, m_texture);

   glUniformMatrix4fv(0, 1, GL_FALSE, &m_projection[0][0]);
   glUniformMatrix4fv(2, 1, GL_FALSE, &m_transform[0][0]);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

ivec2 Text::NextPowerOf2(const ivec2& value)
{
   return ivec2(NextPowerOf2(value.x), NextPowerOf2(value.y));
}

int Text::NextPowerOf2(int value)
{
   int rval = 1;
   while (rval < value)
   {
      rval *= 2;
   }

   return rval;
}

TextBounds Text::GetTextBounds(const FT_Face face, const std::string& text)
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

void Text::UpdateText()
{
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

      int width = glyph->bitmap.width;
      int height = glyph->bitmap.rows;
      int totalWidth = NextPowerOf2(width);
      auto bitmap = glyph->bitmap;

      int verticalOffset = bounds.max.y - glyph->bitmap_top;
      int horizontalOffset = glyph->bitmap_left;

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
void Text::UpdateProjectionMatrix(const ivec2& screenSize)
{
   if (m_screenSize != screenSize)
   {
      m_screenSize = screenSize;

      m_projection = ortho(
         0.f, static_cast<float>(m_screenSize.x),
         0.f, static_cast<float>(m_screenSize.y),
         -1.f, 1.f);
   }
}

void Text::UpdateTransformMatrix()
{
   if (m_transformIsDirty)
   {
      m_transformIsDirty = false;

      m_transform = translate(mat4(), vec3(m_position.x, m_position.y, 0));
   }
}
