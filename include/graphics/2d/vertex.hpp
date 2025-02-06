#pragma once

namespace Nightingale::Graphics::Graphics2D {
    struct Vertex {
        struct Position {
            float x;
            float y;
        } position;

        struct UV {
            float u;
            float v;
        } uv;

        void setPosition(float x, float y) {
            position.x = x;
            position.y = y;
        }

        void setUV(float u, float v) {
            uv.u = u;
            uv.v = v;
        }
    };
}
