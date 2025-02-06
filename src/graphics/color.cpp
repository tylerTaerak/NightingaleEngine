#include <graphics/color.hpp>

namespace Nightingale::Graphics {
    Color::Color() 
        : m_red(1.0), m_green(1.0), m_blue(1.0), m_alpha(1.0) {
    }

    Color::Color(float r, float g, float b) 
        : m_red(r), m_green(g), m_blue(b), m_alpha(1.0) {
    }

    Color::Color(float r, float g, float b, float a)
        : m_red(r), m_green(g), m_blue(b), m_alpha(a) {
    }

    Color::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b) 
        : m_red(r/255.0), m_green(g/255.0), m_blue(g/255.0), m_alpha(1.0) {
    }

    Color::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) 
        : m_red(r/255.0), m_green(g/255.0), m_blue(g/255.0), m_alpha(a/255.0) {
    }

    void Color::r(float r) {
        m_red = r;
    }

    void Color::r(std::uint8_t r) {
        m_red = r / 255.0;
    }

    float Color::r() {
        return m_red;
    }

    std::uint8_t Color::r_int() {
        return static_cast<std::uint8_t>(m_red * 255);
    }

    void Color::g(float g) {
        m_green = g;
    }

    void Color::g(std::uint8_t g) {
        m_green = g / 255.0;
    }

    float Color::g() {
        return m_green;
    }

    std::uint8_t Color::g_int() {
        return static_cast<std::uint8_t>(m_green * 255);
    }

    void Color::b(float b) {
        m_blue = b;
    }

    void Color::b(std::uint8_t b) {
        m_blue = b / 255.0;
    }

    float Color::b() {
        return m_blue;
    }

    std::uint8_t Color::b_int() {
        return static_cast<std::uint8_t>(m_blue * 255);
    }

    void Color::a(float a) {
        m_alpha = a;
    }

    void Color::a(std::uint8_t a) {
        m_alpha = a / 255.0;
    }

    float Color::a() {
        return m_alpha;
    }

    std::uint8_t Color::a_int() {
        return static_cast<std::uint8_t>(m_alpha * 255);
    }

    std::uint32_t Color::rgb() {
        return ((r_int() & 0xff) << 16) + ((g_int() & 0xff) << 8) + (b_int() & 0xff);
    }

    std::uint32_t Color::rgba() {
        return ((r_int() & 0xff) << 24) + ((g_int() & 0xff) << 16) + ((b_int() & 0xff) << 8) + (a_int() & 0xff);
    }

    glm::vec3 Color::asVec3() {
        return glm::vec3 { m_red, m_green, m_blue };
    }

    glm::vec4 Color::asVec4() {
        return glm::vec4 { m_red, m_green, m_blue, m_alpha };
    }
}
