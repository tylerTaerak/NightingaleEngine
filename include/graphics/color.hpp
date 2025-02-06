#pragma once

#include <cstdint>
#include <glm/glm.hpp>
namespace Nightingale::Graphics {
    class Color {
        public:
            Color();

            Color(float r, float g, float b);

            Color(float r, float g, float b, float a);

            Color(std::uint8_t r, std::uint8_t g, std::uint8_t b);

            Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);

            void r(float r);

            void r(std::uint8_t r);

            float r();

            std::uint8_t r_int();

            void g(float g);

            void g(std::uint8_t g);

            float g();

            std::uint8_t g_int();

            void b(float b);

            void b(std::uint8_t b);

            float b();

            std::uint8_t b_int();

            void a(float a);

            void a(std::uint8_t a);

            float a();

            std::uint8_t a_int();

            std::uint32_t rgb();

            std::uint32_t rgba();

            glm::vec3 asVec3();

            glm::vec4 asVec4();
        private:
            float m_red;
            float m_green;
            float m_blue;
            float m_alpha;
    };
}
