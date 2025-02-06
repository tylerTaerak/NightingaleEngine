#include <graphics/2d/camera2d.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utils/logger.hpp>
#include <glm/gtx/string_cast.hpp>


namespace Nightingale::Graphics::Graphics2D {
    Camera2D::Camera2D() 
        : m_position(0.f, 0.f),
        m_cameraMatrix(1.f),
        m_orthoMatrix(1.f),
        m_needsUpdate(true),
        m_scale(1.f),
        m_width(500),
        m_height(500) {
    }

    Camera2D::~Camera2D() {
    }

    void Camera2D::init(int screenWidth, int screenHeight) {
        m_width = screenWidth;
        m_height = screenHeight;

        m_orthoMatrix = glm::ortho(-(float) (m_width / 2.0), (float) (m_width/2.0), -(float) (m_height / 2.0), (float) (m_height / 2.0));
    }

    void Camera2D::setPosition(const glm::vec2 &newPos) {
        m_needsUpdate = true;
        m_position = newPos;
    }

    glm::vec2 Camera2D::getPosition() const {
        return m_position;
    }

    void Camera2D::setScale(float newScale) {
        m_needsUpdate = true;
        m_scale = newScale;
    }

    float Camera2D::getScale() const {
        return m_scale;
    }

    glm::mat4 Camera2D::getCameraMatrix() const {
        return m_cameraMatrix;
    }

    void Camera2D::update() {
        if (m_needsUpdate) {
            glm::vec3 translate(-m_position.x, -m_position.y, 0.f);
            m_cameraMatrix = glm::translate(m_orthoMatrix, translate);
            glm::vec3 scale(m_scale, m_scale, 0.0f);
            m_cameraMatrix = glm::scale(glm::mat4(1.f), scale) * m_cameraMatrix;
        }

        m_needsUpdate = false;
    }

    int Camera2D::getWidth() {
        return m_width;
    }

    int Camera2D::getHeight() {
        return m_height;
    }
}
