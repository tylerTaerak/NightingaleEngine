#include <memory>
#define GL_GLEXT_PROTOTYPES

#include "SDL_video.h"
#include "content_loader.hpp"
#include "game_states/game_mode.hpp"
#include "graphics_interface.hpp"
#include "pushdown_automaton.hpp"
#include "utils/params.hpp"
#include <nightingale.hpp>
#include <ecs/entity.hpp>
#include <utils/logger.hpp>
#include <graphics/default_shaders.hpp>

#include <SDL.h>
#include <SDL_opengl.h>

namespace Nightingale {
    Nightingale::SDL::InputHandler *InputHandler = NULL;
    Nightingale::FSM::PushdownAutomaton *StateHandler = NULL;
    Nightingale::Graphics::GraphicsInterface *GraphicsInterface = NULL;
    Nightingale::Graphics::Graphics2D::Camera2D *Camera;
    Nightingale::SDL::Window *Window = NULL;
    Nightingale::Utils::GameWatch *GameWatch = NULL;
    Nightingale::Content::ContentLoader *ContentLoader = NULL;
    Nightingale::Audio::AudioPlayer *AudioPlayer = NULL;
    bool Quit = false;
    unsigned int DEFAULT_SPRITE_PROGRAM = 0;
    unsigned int DEFAULT_FONT_PROGRAM = 0;

    void initialize() {
        Utils::NightingaleParams defaultParams;

        initialize(defaultParams);
    }

    void initialize(const Utils::NightingaleParams &params) {
        LOG(NG_DEBUG, "STARTING INITIALIZATION");
        SDL_Init(SDL_INIT_EVERYTHING);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        Window = Nightingale::SDL::Window::create(
                params.WindowParams.windowName,
                params.WindowParams.windowWidth,
                params.WindowParams.windowHeight,
                params.WindowParams.sdl_flags);

        LOG(NG_DEBUG, "Created Window");

        Graphics::Color color = params.GraphicsParams.clearColor;
        LOG(NG_DEBUG, "Setting Clear Color - R: " + std::to_string(color.r()) + ", G: " + std::to_string(color.g()) + ", B: " + std::to_string(color.b()) + ", A: " + std::to_string(color.a()));
        glClearColor(color.r(), color.g(), color.b(), color.a());

        GLfloat glColor[3];
        glGetFloatv(GL_COLOR_CLEAR_VALUE, glColor);
        LOG(NG_DEBUG, "OpenGL Current Clear Color - R: " + std::to_string(glColor[0]) + ", G: " + std::to_string(glColor[1]) + ", B: " + std::to_string(glColor[2]));

        SDL_GL_SetSwapInterval(params.GraphicsParams.vsyncEnabled);

        if (params.StateParams.stateMap.size() == 0) {
            LOG(NG_FATAL, "No Game Modes were specified prior to initialization. Exiting...");
        }

        GraphicsInterface = new Graphics::GraphicsInterface;
        Camera = new Graphics::Graphics2D::Camera2D;
        InputHandler = new SDL::InputHandler;
        GameWatch = new Utils::GameWatch;
        ContentLoader = new Content::ContentLoader;
        StateHandler = new FSM::PushdownAutomaton(params.StateParams.stateMap, params.StateParams.startingState);
        AudioPlayer = new Audio::AudioPlayer;

        Camera->init(params.WindowParams.windowWidth, params.WindowParams.windowHeight);
        //Camera->setPosition({params.WindowParams.windowWidth / 2, params.WindowParams.windowHeight / 2});

        DEFAULT_SPRITE_PROGRAM = GraphicsInterface->addNewShaderProgramFromText(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER);
        GraphicsInterface->addAttributeToShader(DEFAULT_SPRITE_PROGRAM, "vertexPosition");
        //GraphicsInterface->addAttributeToShader(DEFAULT_SPRITE_PROGRAM, "vertexColor");
        GraphicsInterface->addAttributeToShader(DEFAULT_SPRITE_PROGRAM, "vertexUV");

        LOG(NG_DEBUG, "INITIALIZED DEFAULT SPRITE PROGRAM: " + std::to_string(DEFAULT_SPRITE_PROGRAM));

        DEFAULT_FONT_PROGRAM = GraphicsInterface->addNewShaderProgramFromText(DEFAULT_FONT_VERTEX_SHADER, DEFAULT_FONT_FRAGMENT_SHADER);
        GraphicsInterface->addAttributeToShader(DEFAULT_FONT_PROGRAM, "vertex");

        LOG(NG_DEBUG, "INITIALIZED DEFAULT FONT PROGRAM: " + std::to_string(DEFAULT_FONT_PROGRAM));

        Quit = false;

        LOG(NG_DEBUG, "Nightingale Initialized");
    }

    void update() {
        StateHandler->update();
        auto currentGameMode = std::dynamic_pointer_cast<GameStates::GameMode>(StateHandler->get_current_state());
        currentGameMode->update(GameWatch->getFrameTime());
        Camera->update();

        GameWatch->tick();
    }

    void draw() {
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto currentGameMode = std::dynamic_pointer_cast<GameStates::GameMode >(StateHandler->get_current_state());
        currentGameMode->draw();

        Window->swapBuffer();
    }

    void run() {
        //run the game loop
        while (!Quit) {
            InputHandler->processInput();
            update();
            draw();
        }
        delete Window;
        delete StateHandler;
        delete GraphicsInterface;
        delete InputHandler;
        delete GameWatch;
        delete ContentLoader;
        delete AudioPlayer;
    }

    void request_exit() {
        Quit = true;
    }

}
