#define GL_EXT_PROTOTYPES
#include <content/content_loader.hpp>
#include <content/content_types.hpp>
#include <utils/logger.hpp>

#include <SDL_image.h>
#include <SDL_opengl.h>

namespace Nightingale::Content {
    template<>
    SpriteSheet ContentLoader::loadContent<SpriteSheet>(const std::string &filepath, int dimX, int dimY) {
        auto it = m_animationCache.find(filepath);

        if (it != m_animationCache.end()) {
            return it->second;
        }

        SpriteSheet ss;

        SDL_Surface *surface = IMG_Load(filepath.c_str());

        int subDimX = surface->w / dimX;
        int subDimY = surface->h / dimY;

        ss.m_width = subDimX;
        ss.m_height = subDimY;

        ss.m_xSize = dimX;
        ss.m_ySize = dimY;

        ss.m_currX = 0;
        ss.m_currY = 0;

        for (int j=0; j<dimY; j++) {
            ss.m_textureIds.push_back(std::vector<std::uint32_t>{});

            for (int i=0; i<dimX; i++) {
                std::uint32_t id = 0;

                SDL_Surface *subSurface = SDL_CreateRGBSurface(0, subDimX, subDimY, 32, 0, 0, 0, 0);

                SDL_Rect srcRect;

                srcRect.x = i * subDimX;
                srcRect.y = j * subDimY;
                srcRect.w = subDimX;
                srcRect.h = subDimY;

                int err = SDL_BlitSurface(surface, &srcRect, subSurface, NULL); // now we have our surface to send to OpenGL
                
                if (err) {
                    LOG(NG_ERROR, "Failed to divide sprite sheet into subsurface; Error: " + std::string(SDL_GetError()));
                }

                glGenTextures(1, &(ss.m_textureIds[j][i]));

                if ((err = glGetError()) != GL_NO_ERROR) {
                    LOG(NG_ERROR, "Failed to generate new GL texture");
                }

                glBindTexture(GL_TEXTURE_2D, ss.m_textureIds[j][i]);

                if ((err = glGetError()) != GL_NO_ERROR) {
                    LOG(NG_ERROR, "Failed to bind GL texture");
                }

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, subSurface->w, subSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, subSurface->pixels);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                if ((err = glGetError()) != GL_NO_ERROR) {
                    LOG(NG_ERROR, "Failed to create 2D Texture for OpenGL");
                }
                
                SDL_FreeSurface(surface);
            }
        }

        return ss;
    }

    std::uint32_t SpriteSheet::getCurrentTextureId() {
        return m_textureIds[m_currY][m_currX];
    }

    std::uint32_t SpriteSheet::getTextureWidth() {
        return m_width;
    }

    std::uint32_t SpriteSheet::getTextureHeight() {
        return m_height;
    }
}
