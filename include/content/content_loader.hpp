#pragma once

#include <map>
#include <string>
#include "content_types.hpp"
#include <freetype2/freetype/freetype.h>

namespace Nightingale::Content {
    class ContentLoader {
        public:
            ContentLoader();
            ~ContentLoader();

            template <typename T>
            T loadContent(const std::string &filepath);

            template <typename T>
            T loadContent(const std::string &filepath, int dimX, int dimY);

            template <typename T>
            T loadContent(const std::string &filepath, float fontSize);

        private:
            std::map<std::string , Texture2D> m_textureCache;
            std::map<std::string, Font> m_fontCache;
            std::map<std::string, Music> m_musicCache;
            std::map<std::string, SoundEffect> m_soundCache;
            std::map<std::string, SpriteSheet> m_animationCache;

            FT_Library m_library;
    };
}
