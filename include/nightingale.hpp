#pragma once

#include "audio_player.hpp"
#include "camera2d.hpp"
#include "content/content_loader.hpp"
#include "utils/game_watch.hpp"
#include <utils/params.hpp>
#include <sdl/input_handler.hpp>
#include <state_machines/pushdown_automaton.hpp>
#include <graphics/graphics_interface.hpp>
#include <sdl/window.hpp>

namespace Nightingale {
    extern void initialize();

    extern void initialize(const Utils::NightingaleParams &params);

    extern void update();

    extern void draw();

    extern void run();

    extern void request_exit();

    extern void cleanup();

    extern SDL::InputHandler *InputHandler;
    extern FSM::PushdownAutomaton *StateHandler;
    extern Graphics::GraphicsInterface *GraphicsInterface;
    extern Graphics::Graphics2D::Camera2D *Camera;
    extern SDL::Window *Window;
    extern Utils::GameWatch *GameWatch;
    extern Content::ContentLoader *ContentLoader;
    extern Audio::AudioPlayer *AudioPlayer;
    extern bool Quit;
    extern unsigned int DEFAULT_SPRITE_PROGRAM;
    extern unsigned int DEFAULT_FONT_PROGRAM;
}
