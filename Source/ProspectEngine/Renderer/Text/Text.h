#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "EngineDefines.h"
#include "Renderer/Shaders/Shader.h"

#include <glm/mat4x4.hpp>

namespace Prospect
{
   //Relative to origin baseline.
   struct TextBounds
   {
      glm::ivec2 min;
      glm::ivec2 max;
      glm::ivec2 size;
   };

   class Text
   {
   public:
      Text(const std::string& text, const glm::ivec2& position, int size);

      void SetText(const std::string& text);
      void SetPosition(const glm::ivec2 position);

      void Render(const glm::ivec2& screenSize);

   private:
      void InitialiseFont(int size);
      void CreateBuffers();
      void UpdateText();
      void UpdateProjectionMatrix(const glm::ivec2& screenSize);
      void UpdateTransformMatrix();

      static TextBounds GetTextBounds(const FT_Face face, const std::string& text);
      static glm::ivec2 NextPowerOf2(const glm::ivec2& value);
      static int NextPowerOf2(int value);

      FT_Library m_library;
      FT_Face m_face;
      std::string m_text;

      GLuint m_texture;
      Shader& m_shader;

      GLuint m_VAO;

      const enum Buffers
      {
         BUFFER_POSITIONS,
         BUFFER_TEXTURECOORDS,
         BUFFER_COUNT
      };

      GLuint m_buffers[BUFFER_COUNT];

      glm::mat4 m_transform;
      glm::mat4 m_projection;
      glm::ivec2 m_screenSize;
      glm::ivec2 m_position;

      mutable bool m_textIsDirty;
      mutable bool m_transformIsDirty;
   };
}
