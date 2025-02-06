#include <sdl/window.hpp>
#include <SDL_opengl.h>
#include <utils/logger.hpp>

namespace Nightingale::SDL {

    Window *Window::create(std::string windowName, uint screenWidth, uint screenHeight, std::uint32_t flags) {
        Window *window = new Window;

        window->m_width = screenWidth;
        window->m_height = screenHeight;

        window->m_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

        if (window->m_sdlWindow == nullptr) {
            LOG(NG_FATAL, "Failed to create SDL Window");
        }

        SDL_GLContext glContext = SDL_GL_CreateContext(window->m_sdlWindow);

        if (glContext == nullptr) {
            LOG(NG_FATAL, "SDL OpenGL Context could not be created");
        }

        if (SDL_GL_MakeCurrent(window->m_sdlWindow, glContext)) {
            LOG(NG_FATAL, SDL_GetError());
        }

        return window;
    }

    void Window::swapBuffer() {
        SDL_GL_SwapWindow(m_sdlWindow);
    }

    uint Window::getScreenWidth() {
        return m_width;
    }

    uint Window::getScreenHeight() {
        return m_height;
    }
}
