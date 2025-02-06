#define GL_EXT_PROTOTYPES
#include <content/content_loader.hpp>
#include <content/content_types.hpp>
#include <utils/logger.hpp>

#include <SDL_image.h>
#include <SDL_opengl.h>

namespace Nightingale::Content {

    template <>
    Texture2D ContentLoader::loadContent<Texture2D>(const std::string &filepath) {
        auto it = m_textureCache.find(filepath);

        if (it != m_textureCache.end()) {
            return it->second;
        }

        Texture2D tex;

        SDL_Surface *surface = IMG_Load(filepath.c_str());

        if (surface == nullptr) {
            LOG(NG_ERROR, "Failed to load texture file: " + filepath + "; Error Message: " + std::string(SDL_GetError()));
        }

        tex.m_width = surface->w;
        tex.m_height = surface->h;

        GLenum err;
        
        glGenTextures(1, &(tex.m_textureId));

        if ((err = glGetError()) != GL_NO_ERROR) {
            LOG(NG_ERROR, "Failed to generate new GL texture");
        }

        glBindTexture(GL_TEXTURE_2D, tex.m_textureId);

        if ((err = glGetError()) != GL_NO_ERROR) {
            LOG(NG_ERROR, "Failed to bind GL texture");
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if ((err = glGetError()) != GL_NO_ERROR) {
            LOG(NG_ERROR, "Failed to create 2D Texture for OpenGL");
        }
        
        SDL_FreeSurface(surface);

        return tex;
    }

    std::uint32_t Texture2D::getId() {
        return m_textureId;
    }

    std::uint32_t Texture2D::getWidth() {
        return m_width;
    }

    std::uint32_t Texture2D::getHeight() {
        return m_height;
    }
}
