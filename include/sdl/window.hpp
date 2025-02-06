#pragma once

#include <string>
#include <SDL.h>
#include <cstdint>

namespace Nightingale::SDL {
    class Window {
        public:
            static Window *create(std::string windowName, uint screenWidth, uint screenHeight, std::uint32_t flags);

            void swapBuffer();

            uint getScreenWidth();

            uint getScreenHeight();
        private:
            SDL_Window *m_sdlWindow;

            uint m_width;
            uint m_height;
    };
}
