#pragma once

#include <random>
#include "content/content_types.hpp"
#include "particle.hpp"

#define MAX_PARTICLES 10000

namespace Nightingale::Graphics::Particles {
    class ParticleGenerator {
        public:
            ParticleGenerator();
            ~ParticleGenerator();

            void generateParticlesFromPoint(std::uint32_t numParticles, float x, float y, float width, float height, float minSpeed, float maxSpeed, float timeout_ms, Content::Texture2D texture);

            void update();

            void draw();

        private:
            bool goToNextIndex();

            Particle m_particles[MAX_PARTICLES];
            std::size_t m_currentIndex;
            std::mt19937 m_rng;
    };
}
