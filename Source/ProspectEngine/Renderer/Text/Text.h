#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Resources/Resources.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace Prospect
{
   class Text
   {
   public:
      Text(const std::string& text)
         :
         m_text(text)
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

         error = FT_Set_Pixel_Sizes(m_face, 0, 16);

         UpdateText();
      }

      void UpdateText()
      {
         auto chars = m_text.c_str();
         int penX = 300;
         int penY = 200;
         FT_GlyphSlot slot = m_face->glyph;

         for (int i = 0; i < m_text.size(); i++)
         {
            FT_Load_Char(m_face, chars[i], FT_LOAD_RENDER);

            RenderToFile(
               slot->bitmap,
               penX + slot->bitmap_left,
               penY - slot->bitmap_top);

            penX += slot->advance.x >> 6;
         }
      }

      //TODO: Combine slots then render to a single texture.
      void RenderToFile(FT_Bitmap& image, int posX, int posY)
      {
         std::string filename("testtext" + std::to_string(posX) + ".bmp");
         auto success = stbi_write_bmp(filename.c_str(), image.width, image.rows, 1, &image.buffer[0]);
      }

   private:
      FT_Library m_library;
      FT_Face m_face;
      std::string m_text;
   };
}
