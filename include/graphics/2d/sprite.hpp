#pragma once

#include <string>
#include "content/content_types.hpp"
#include "ecs/component.hpp"
#include "vertex.hpp"

namespace Nightingale::Graphics::Graphics2D {
    class Sprite : public ECS::Component{
        public:
            Sprite();
            ~Sprite();

            void init(const std::string &texture);

            void draw(float x, float y, float width, float height);

            void draw(float x, float y);
        private:
            unsigned int m_vboId;
            unsigned int m_vaoId;

            Vertex m_vertices[6];

            Content::Texture2D m_texture;
    };
}
