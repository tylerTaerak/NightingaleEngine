#include <iostream>
#define GL_GLEXT_PROTOTYPES

#include "SDL_opengl.h"
#include "freetype/freetype.h"
#include "utils/logger.hpp"
#include <content/content_loader.hpp>
#include <content/content_types.hpp>

namespace Nightingale::Content {
    template<>
    Font ContentLoader::loadContent<Font>(const std::string &filepath, float fontSize) {
        auto it = m_fontCache.find(filepath);

        if (it != m_fontCache.end()) {
            return it->second;
        }

        Font f;
        FT_Face face;


        if (FT_New_Face(m_library, filepath.c_str(), 0, &face)) {
            LOG(NG_ERROR, "Error loading new font face from filepath: " + filepath);
        }

        FT_Set_Pixel_Sizes(face, 0, fontSize);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned char c=0; c<128; c++) {
            FT_Error err = FT_Load_Char(face, c, FT_LOAD_RENDER);
            if (err) {
                LOG(NG_ERROR, "FreeType Failed to Load Glyph: " + std::to_string(c) + "; Error Code: " + std::to_string(err));
                std::cout << FT_Error_String(err) << std::endl;
                continue;
            }

            Texture2D tex;
            tex.m_width = face->glyph->bitmap.width;
            tex.m_height = face->glyph->bitmap.rows;

            glGenTextures(1, &(tex.m_textureId));
            glBindTexture(GL_TEXTURE_2D, tex.m_textureId);
            glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    tex.m_width,
                    tex.m_height,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Font::Glyph glyph = {
                tex,
                face->glyph->bitmap_left,
                face->glyph->bitmap_top,
                face->glyph->advance.x
            };

            f.m_glyphMap.emplace(c, glyph);
        }

        FT_Done_Face(face);

        return f;
    }

    Font::Glyph Font::getGlyphData(unsigned char c) {
        return m_glyphMap[c];
    }
}
