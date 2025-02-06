#pragma once

#include "content/content_types.hpp"
#include "graphics/2d/vertex.hpp"

namespace Nightingale::Graphics::Particles {

    enum class ParticleType {
        PARTICLE_STATIC,
        PARTICLE_ANIMATED
    };

    struct Particle {
        Particle();
        ~Particle();

        bool enabled = false;

        struct {
            float x;
            float y;
            float z;
        } position;

        struct {
            float x;
            float y;
            float z;
        } velocity;

        struct {
            float width;
            float height;
            float depth;
        } dimensions;

        float remainingTime_ms;

        struct TextureData{
            ParticleType type;

            union Texture {
                constexpr Texture() : nondata('\0') {}
                ~Texture() {}

                unsigned char nondata;
                Content::SpriteSheet spritesheet;
                Content::Texture2D texture2d;
            } texture;
        };

        TextureData textureData;

        void draw();

        private:
            Graphics2D::Vertex m_vertices[6];
            uint m_id;
    };
}
