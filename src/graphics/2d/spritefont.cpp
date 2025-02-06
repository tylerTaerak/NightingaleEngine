#define GL_GLEXT_PROTOTYPES

#include "nightingale.hpp"
#include <graphics/2d/spritefont.hpp>

namespace Nightingale::Graphics::Graphics2D {
    SpriteFont::SpriteFont() 
        : ECS::Component(1'000'001) {
    }

    SpriteFont::~SpriteFont() {
    }

    void SpriteFont::init(const std::string &fontpath, float fontSize) {
        m_font = ContentLoader->loadContent<Content::Font>(fontpath, fontSize);

        glGenVertexArrays(1, &m_vaoId);
        glGenBuffers(1, &m_vboId);
        glBindVertexArray(m_vaoId);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void SpriteFont::draw(std::string text, float x, float y, float scale, Color color) {
        auto prog = Nightingale::GraphicsInterface->useProgram(DEFAULT_FONT_PROGRAM);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(m_vaoId);

        Nightingale::GraphicsInterface->setUniformForShader(DEFAULT_FONT_PROGRAM, "text", 0);
        Nightingale::GraphicsInterface->setUniformForShader(DEFAULT_FONT_PROGRAM, "textColor", color.asVec3());
        Nightingale::GraphicsInterface->setUniformForShader(DEFAULT_FONT_PROGRAM, "projectionMatrix", Camera->getCameraMatrix());

        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++) {
            Content::Font::Glyph glyph = m_font.getGlyphData(*c);

            float xpos = x + glyph.x_bearing * scale;
            float ypos = y;

            float w = glyph.texture.getWidth() * scale;
            float h = glyph.texture.getHeight() * scale;

            float vertices[6][4] = {
                { xpos, ypos + h, 0.f, 0.f },
                { xpos, ypos,     0.f, 1.f },
                { xpos + w, ypos, 1.f, 1.f },

                { xpos, ypos + h, 0.f, 0.f },
                { xpos + w, ypos, 1.f, 1.f },
                { xpos + w, ypos + h, 1.f, 0.f }
            };

            glBindTexture(GL_TEXTURE_2D, glyph.texture.getId());

            glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            x += (glyph.advance >> 6) * scale;
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glDisable(GL_BLEND);
    }

    void SpriteFont::draw(std::string text, float x, float y, float scale) {
        draw(text, x, y, scale, Color{1.f, 1.f, 1.f, 1.f});
    }

    void SpriteFont::draw(std::string text, float x, float y) {
        draw(text, x, y, 1.0, Color{1.f, 1.f, 1.f, 1.f});
    }
}
