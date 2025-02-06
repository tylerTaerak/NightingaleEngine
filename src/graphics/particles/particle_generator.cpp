#define GL_GLEXT_PROTOTYPES
#include "SDL_opengl.h"
#include "graphics/2d/vertex.hpp"
#include "nightingale.hpp"

#include <cmath>
#include <graphics/particles/particle_generator.hpp>
#include <random>

namespace Nightingale::Graphics::Particles {
    ParticleGenerator::ParticleGenerator() :
        m_rng(std::random_device{}()), m_currentIndex(0) {
    }

    ParticleGenerator::~ParticleGenerator() {
    }

    void ParticleGenerator::generateParticlesFromPoint(std::uint32_t numParticles, float x, float y, float width, float height, float minSpeed, float maxSpeed, float timeout_ms, Content::Texture2D texture) {
        for (std::uint32_t i=0; i<numParticles; i++) {
            if (!goToNextIndex()) {
                return;
            }
            std::uniform_real_distribution<float> dist(minSpeed, maxSpeed);

            float speed = dist(m_rng);

            float xrand = dist(m_rng);
            float yrand = dist(m_rng);

            float sum = std::pow(xrand, 2);
            sum += std::pow(yrand, 2);

            sum = std::pow(sum, 0.5);

            xrand /= sum;
            yrand /= sum;

            Particle &p = m_particles[m_currentIndex];

            p.position.x = x;
            p.position.y = y;
            p.position.z = 0;

            p.velocity.x = xrand * speed;
            p.velocity.y = yrand * speed;
            p.velocity.z = 0;

            p.dimensions.width = width;
            p.dimensions.height = height;
            p.dimensions.depth = 0;

            p.remainingTime_ms = timeout_ms;
            p.enabled = true;

            p.textureData.type = ParticleType::PARTICLE_STATIC;
            p.textureData.texture.texture2d = texture;
        }
    }

    void ParticleGenerator::update() {
        std::vector<int> toRemove;
        for (int i=0; i<MAX_PARTICLES; i++) {
            Particle &particle = m_particles[i];

            particle.position.x += particle.velocity.x;
            particle.position.y += particle.velocity.y;
            particle.position.z += particle.velocity.z;

            particle.remainingTime_ms -= GameWatch->getFrameTime();

            if (particle.remainingTime_ms <= 0 && !particle.enabled) {
                particle.enabled = false;
            }
        }
    }

    void ParticleGenerator::draw() {
        for (std::size_t i=0; i<MAX_PARTICLES; i++) {
            if (m_particles[i].enabled) {
                m_particles[i].draw();
            }
        }
    }

    bool ParticleGenerator::goToNextIndex() {
        int nextIndex = m_currentIndex;
        while((++nextIndex % MAX_PARTICLES) != m_currentIndex) {
            if (!m_particles[nextIndex].enabled) {
                m_currentIndex = nextIndex;
                return true;
            }
        }

        return false;
    }

    Particle::Particle() {
        glGenBuffers(1, &m_id);

        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Particle::~Particle() {
    }

    void Particle::draw() {
        Graphics2D::Vertex vertices[6];


        m_vertices[0].setPosition(position.x + dimensions.width, position.y + dimensions.height);
        m_vertices[0].setUV(1.f, 1.f);
        m_vertices[1].setPosition(position.x, position.y + dimensions.height);
        m_vertices[1].setUV(0.f, 1.f);
        m_vertices[2].setPosition(position.x, position.y);
        m_vertices[2].setUV(0.f, 0.f);
        m_vertices[3].setPosition(position.x, position.y);
        m_vertices[3].setUV(0.f, 0.f);
        m_vertices[4].setPosition(position.x + dimensions.width, position.y);
        m_vertices[4].setUV(1.f, 0.f);
        m_vertices[5].setPosition(position.x + dimensions.width, position.y + dimensions.height);
        m_vertices[5].setUV(1.f, 1.f);

        switch(textureData.type) {
            case ParticleType::PARTICLE_ANIMATED:
                glBindTexture(GL_TEXTURE_2D, textureData.texture.spritesheet.getCurrentTextureId());
                break;
            case ParticleType::PARTICLE_STATIC:
                glBindTexture(GL_TEXTURE_2D, textureData.texture.texture2d.getId());
                break;
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_id);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Graphics2D::Vertex), (void *) offsetof(Graphics2D::Vertex, position));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Graphics2D::Vertex), (void *) offsetof(Graphics2D::Vertex, uv));

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
