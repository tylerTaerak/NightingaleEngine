#pragma once

#include <SDL.h>

namespace Nightingale::SDL {
    enum class InputEventType : uint {
        EVENT_MOUSEBUTTONDOWN,
        EVENT_MOUSEBUTTONUP,
        EVENT_MOUSEMOTION,
        EVENT_MOUSEWHEEL,
        EVENT_KEYDOWN,
        EVENT_KEYUP,
        EVENT_CONTROLLERJOYSTICK,
        EVENT_CONTROLLERBUTTONDOWN,
        EVENT_CONTROLLERBUTTONUP,
        EVENT_CONTROLLERCONNECT,
        EVENT_CONTROLLERDISCONNECT,
        EVENT_CONTROLLERREMAP,
        EVENT_QUIT,
        EVENT_NONE
    };

    enum class WindowFlags : uint32_t {
        FULLSCREEN = SDL_WINDOW_FULLSCREEN,
        FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP,
        OPENGL = SDL_WINDOW_OPENGL,
        VULKAN = SDL_WINDOW_VULKAN,
        METAL = SDL_WINDOW_METAL,
        HIDDEN = SDL_WINDOW_HIDDEN,
        BORDERLESS = SDL_WINDOW_BORDERLESS,
        RESIZABLE = SDL_WINDOW_RESIZABLE,
        MINIMIZED = SDL_WINDOW_MINIMIZED,
        MAXIMIZED = SDL_WINDOW_MAXIMIZED,
        INPUT_GRABBED = SDL_WINDOW_INPUT_GRABBED,
        ALLOW_HIGHDPI = SDL_WINDOW_ALLOW_HIGHDPI
    };

    enum class Keys : uint {
        A = SDLK_a,
        B = SDLK_b,
        C = SDLK_c,
        D = SDLK_d,
        E = SDLK_e,
        F = SDLK_f,
        G = SDLK_g,
        H = SDLK_h,
        I = SDLK_i,
        J = SDLK_j,
        K = SDLK_k,
        L = SDLK_l,
        M = SDLK_m,
        N = SDLK_n,
        O = SDLK_o,
        P = SDLK_p,
        Q = SDLK_q,
        R = SDLK_r,
        S = SDLK_s,
        T = SDLK_t,
        U = SDLK_u,
        V = SDLK_v,
        W = SDLK_w,
        X = SDLK_x,
        Y = SDLK_y,
        Z = SDLK_z,

        ENTER = SDLK_RETURN,
        ESCAPE = SDLK_ESCAPE,
        BACKSPACE = SDLK_BACKSPACE,
        TAB = SDLK_TAB,
        SPACE = SDLK_SPACE,
        EXCLM_PT = SDLK_EXCLAIM,
        DB_QUOTE = SDLK_QUOTEDBL,
        HASH = SDLK_HASH,
        PERCENT = SDLK_PERCENT,
        DOLLAR = SDLK_DOLLAR,
        AMPERSAND = SDLK_AMPERSAND,
        SNG_QUOTE = SDLK_QUOTE,
        LPAREN = SDLK_LEFTPAREN,
        RPAREN = SDLK_RIGHTPAREN,
        ASTERISK = SDLK_ASTERISK,
        PLUS = SDLK_PLUS,
        COMMA = SDLK_COMMA,
        MINUS = SDLK_MINUS,
        PERIOD = SDLK_PERIOD,
        FSLASH = SDLK_SLASH,
        ZERO = SDLK_0,
        ONE = SDLK_1,
        TWO = SDLK_2,
        THREE = SDLK_3,
        FOUR = SDLK_4,
        FIVE = SDLK_5,
        SIX = SDLK_6,
        SEVEN = SDLK_7,
        EIGHT = SDLK_8,
        NINE = SDLK_9,
        COLON = SDLK_COLON,
        SM_COLON = SDLK_SEMICOLON,
        LT = SDLK_LESS,
        EQ = SDLK_EQUALS,
        GT = SDLK_GREATER,
        QMARK = SDLK_QUESTION,
        AT = SDLK_AT,
        LBRACKET = SDLK_LEFTBRACKET,
        RBRACKET = SDLK_RIGHTBRACKET,
        BKSLASH = SDLK_BACKSLASH,
        CARET = SDLK_CARET,
        UNDERSCORE = SDLK_UNDERSCORE,
        BACKQUOTE = SDLK_BACKQUOTE,
        
        CAPSLOCK = SDLK_CAPSLOCK,

        F1 = SDLK_F1,
        F2 = SDLK_F2,
        F3 = SDLK_F3,
        F4 = SDLK_F4,
        F5 = SDLK_F5,
        F6 = SDLK_F6,
        F7 = SDLK_F7,
        F8 = SDLK_F8,
        F9 = SDLK_F9,
        F10 = SDLK_F10,
        F11 = SDLK_F11,
        F12 = SDLK_F12,
        F13 = SDLK_F13,
        F14 = SDLK_F14,
        F15 = SDLK_F15,
        F16 = SDLK_F16,
        F17 = SDLK_F17,
        F18 = SDLK_F18,
        F19 = SDLK_F19,
        F20 = SDLK_F20,
        F21 = SDLK_F21,
        F22 = SDLK_F22,
        F23 = SDLK_F23,
        F24 = SDLK_F24,

        PRNTSCREEN = SDLK_PRINTSCREEN,
        SCROLL_LOCK = SDLK_SCROLLLOCK,
        PAUSE = SDLK_PAUSE,
        INSERT = SDLK_INSERT,
        HOME = SDLK_HOME,
        PG_UP = SDLK_PAGEUP,
        DELETE = SDLK_DELETE,
        END = SDLK_END,
        PG_DOWN = SDLK_PAGEDOWN,

        RIGHT = SDLK_RIGHT,
        LEFT = SDLK_LEFT,
        DOWN = SDLK_DOWN,
        UP = SDLK_UP,

        NUMLOCK = SDLK_NUMLOCKCLEAR,
        NUMPAD_DIVIDE = SDLK_KP_DIVIDE,
        NUMPAD_MULTIPLY = SDLK_KP_MULTIPLY,
        NUMPAD_MINUS = SDLK_KP_MINUS,
        NUMPAD_PLUS = SDLK_KP_PLUS,
        NUMPAD_ENTER = SDLK_KP_ENTER,
        NUMPAD_1 = SDLK_KP_1,
        NUMPAD_2 = SDLK_KP_2,
        NUMPAD_3 = SDLK_KP_3,
        NUMPAD_4 = SDLK_KP_4,
        NUMPAD_5 = SDLK_KP_5,
        NUMPAD_6 = SDLK_KP_6,
        NUMPAD_7 = SDLK_KP_7,
        NUMPAD_8 = SDLK_KP_8,
        NUMPAD_9 = SDLK_KP_9,
        NUMPAD_0 = SDLK_KP_0,
        NUMPAD_PERIOD = SDLK_KP_PERIOD,

        LCTRL = SDLK_LCTRL,
        LSHIFT = SDLK_LSHIFT,
        LALT = SDLK_LALT,
        LGUI = SDLK_LGUI,
        RCTRL = SDLK_RCTRL,
        RSHIFT = SDLK_RSHIFT,
        RALT = SDLK_RALT,
        RGUI = SDLK_RGUI
    };

    struct InputEvent {
        private:
            struct Event {
                virtual ~Event() = default;
            };

        public:
            InputEventType event_type;
            Event *event;

            struct MouseButtonEvent : public Event {
                InputEventType type;
                bool pressed;
                uint8_t clicks;
                int32_t x_pos;
                int32_t y_pos;
            };

            struct MouseMotionEvent : public Event {
                InputEventType type;
                int32_t x_pos;
                int32_t y_pos;
                int32_t x_pos_relative;
                int32_t y_pos_relative;
            };

            struct MouseWheelEvent : public Event {
                InputEventType type;
                float x_dist;
                float y_dist;
            };

            struct KeyPressEvent : public Event {
                InputEventType type;
                bool pressed;
                Keys key;
            };

            struct ControllerJoystickEvent : public Event {
                InputEventType type;
                uint32_t index;
                int8_t axis;
                int16_t value;
            };

            struct ControllerButtonEvent : public Event {
                InputEventType type;
                uint32_t index;
                uint8_t button;
                bool pressed;
            };

            struct ControllerConnectEvent : public Event {
                InputEventType type;
                int32_t id;
            };

            struct QuitEvent : public Event {
            };
    };


}
