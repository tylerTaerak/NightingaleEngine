#pragma once

#include "graphics/color.hpp"
#include "state_machines/fsm.hpp"
#include <SDL_opengl.h>
#include <cstdint>
#include <string>
#include <sdl/nightingale_typedefs.hpp>

namespace Nightingale::Utils {
    class NightingaleParams {
        public:
            NightingaleParams() {
                WindowParams.windowName = "Nightingale Game";
                WindowParams.windowWidth = 800;
                WindowParams.windowHeight = 800;
                WindowParams.sdl_flags = 0;
                WindowParams.setFlag(SDL::WindowFlags::OPENGL, true);
                
                GraphicsParams.clearColor = Graphics::Color(0.2f, 1.0f, 1.0f);
                GraphicsParams.vsyncEnabled = true;

            }

            struct windowParams {
                std::string windowName;
                std::uint16_t windowWidth;
                std::uint16_t windowHeight;
                std::uint32_t sdl_flags;

                void setFlag(const SDL::WindowFlags &flag, bool enable) {
                    std::uint32_t castFlag = static_cast<std::uint32_t>(flag);
                    if (enable) {
                        sdl_flags |= castFlag;
                    } else {
                        sdl_flags &= ~castFlag;
                    }
                }

                void setWindowDimensions(std::uint16_t width, std::uint16_t height) {
                    windowWidth = width;
                    windowHeight = height;
                }
            } WindowParams;

            struct graphicsParams {
                Graphics::Color clearColor;
                bool vsyncEnabled;

                private:
                    friend class NightingaleParams;
            } GraphicsParams;

            struct stateParams {
                std::map<std::size_t, std::shared_ptr<FSM::FsmState>> stateMap;
                std::size_t startingState;
            } StateParams;
    };
}
