#pragma once

#include "content/content_types.hpp"
#include "graphics/color.hpp"
#include <ecs/component.hpp>
#include <string>

namespace Nightingale::Graphics::Graphics2D {
    class SpriteFont : public ECS::Component {
        public:
            SpriteFont();
            ~SpriteFont();

            void init(const std::string &fontpath, float fontSize);

            void draw(std::string text, float x, float y, float scale, Color color);

            void draw(std::string text, float x, float y, float scale);

            void draw(std::string text, float x, float y);
        private:
            Content::Font m_font;

            uint m_vaoId;
            uint m_vboId;
    };
}
