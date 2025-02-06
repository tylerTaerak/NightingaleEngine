#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <freetype2/freetype/freetype.h>

namespace Nightingale::Content {
    class Texture2D {
        public:
            std::uint32_t getId();

            std::uint32_t getWidth();

            std::uint32_t getHeight();
        private:
            std::uint32_t m_textureId;
            std::uint32_t m_width;
            std::uint32_t m_height;

            friend class ContentLoader;
    };

    class Font {
        public:
            struct Glyph {
                Texture2D texture;
                int x_bearing;
                int y_bearing;
                long advance;
            };

            Glyph getGlyphData(unsigned char c);
        private:
            std::map<unsigned char, Glyph> m_glyphMap;
            friend class ContentLoader;
    };

    class Music {
        public:
            std::uint32_t getSourceId();

            std::uint32_t getBufferId();
        private:
            std::uint32_t m_sourceId;
            std::uint32_t m_bufferId;
            friend class ContentLoader;
    };

    class SoundEffect {
        public:
            std::uint32_t getSourceId();

            std::uint32_t getBufferId();
        private:
            std::uint32_t m_sourceId;
            std::uint32_t m_bufferId;
            friend class ContentLoader;
    };
    
    class SpriteSheet {
        public:
            std::uint32_t getCurrentTextureId();

            std::uint32_t getTextureWidth();

            std::uint32_t getTextureHeight();

            void next();

            void nextNoWrap();
        private:
            std::vector<std::vector<std::uint32_t>> m_textureIds;
            std::uint32_t m_width;
            std::uint32_t m_height;
            std::size_t m_xSize;
            std::size_t m_ySize;
            std::size_t m_currX;
            std::size_t m_currY;

            friend class ContentLoader;
    };
}
