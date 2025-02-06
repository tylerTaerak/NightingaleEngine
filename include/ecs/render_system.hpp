#pragma once

#include "ecs/system.hpp"

namespace Nightingale::ECS {
    /**
     * @class RenderSystem
     *
     * This class is a sub-interface of System,
     * which gives an inherited class not only the
     * update() method, but also a draw() method,
     * which is used to draw Sprites, Particles, and
     * SpriteFonts to the screen.
     */
    class RenderSystem : public System {
        public:
            RenderSystem(std::vector<std::size_t> types)
                : System(types) {
            }
            virtual void draw() = 0;
    };
}
