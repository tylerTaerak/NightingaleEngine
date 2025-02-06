#include "content_types.hpp"
#define GL_GLEXT_PROTOTYPES

#include "nightingale.hpp"
#include <graphics/2d/sprite.hpp>
#include <SDL_opengl.h>
#include <utils/logger.hpp>

namespace Nightingale::Graphics::Graphics2D {
    Sprite::Sprite() 
        : ECS::Component(1'000'000), m_vboId(0), m_vaoId(0) {
        LOG(NG_DEBUG, "Initializing Sprite component with id of 1,000,000");
    }

    Sprite::~Sprite() {
    }

    void Sprite::init(const std::string &texture) {
        glGenBuffers(1, &m_vboId);
        glGenVertexArrays(1, &m_vaoId);
        glBindVertexArray(m_vaoId);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, position));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindVertexArray(0);

        m_texture = Nightingale::ContentLoader->loadContent<Content::Texture2D>(texture);
    }

    void Sprite::draw(float x, float y, float width, float height) {
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        auto prog = Nightingale::GraphicsInterface->useProgram(DEFAULT_SPRITE_PROGRAM);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture.getId());
        Nightingale::GraphicsInterface->setUniformForShader(DEFAULT_SPRITE_PROGRAM, "texSampler", 0);
        Nightingale::GraphicsInterface->setUniformForShader(DEFAULT_SPRITE_PROGRAM, "projectionMatrix", Camera->getCameraMatrix());

        m_vertices[0].setPosition(x, y); // bottom left
        m_vertices[0].setUV(0.f, 0.f);
        m_vertices[1].setPosition(x + width, y + height); // top right
        m_vertices[1].setUV(1.f, 1.f);
        m_vertices[2].setPosition(x, y + height); // top left
        m_vertices[2].setUV(0.f, 1.f);
        m_vertices[3].setPosition(x, y); // bottom left
        m_vertices[3].setUV(0.f, 0.f);
        m_vertices[4].setPosition(x + width, y); // bottom right
        m_vertices[4].setUV(1.f, 0.f);
        m_vertices[5].setPosition(x + width, y + height); // top right
        m_vertices[5].setUV(1.f, 1.f);

        glBindVertexArray(m_vaoId);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
    }

    void Sprite::draw(float x, float y) {
        draw(x, y, m_texture.getWidth(), m_texture.getHeight());
    }
}
