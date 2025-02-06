#pragma once

#include <glm/glm.hpp>

namespace Nightingale::Graphics::Graphics2D {
    class Camera2D {
        public:
            Camera2D();
            ~Camera2D();

            void init(int screenWidth, int screenHeight);

            void setPosition(const glm::vec2 &newPos);
            glm::vec2 getPosition() const;

            void setScale(float newScale);
            float getScale() const;

            glm::mat4 getCameraMatrix() const;

            void update();

            int getWidth();

            int getHeight();

        private:
            bool m_needsUpdate;
            glm::vec2 m_position;
            glm::mat4 m_cameraMatrix;
            glm::mat4 m_orthoMatrix;
            float m_scale;
            
            int m_width;
            int m_height;
    };
}
