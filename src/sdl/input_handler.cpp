#include "sdl/nightingale_typedefs.hpp"
#include <sdl/input_handler.hpp>
#include <utils/logger.hpp>

namespace Nightingale::SDL {
    InputHandler::InputHandler() {
    }

    InputHandler::~InputHandler() {
    }

    void InputHandler::processInput() {
        SDL_Event evt;
        InputEvent inputEvent;

        InputEvent::MouseMotionEvent *mm;
        InputEvent::MouseButtonEvent *mb;
        InputEvent::MouseWheelEvent *mw;
        InputEvent::KeyPressEvent *kp;
        InputEvent::ControllerJoystickEvent *joy;
        InputEvent::ControllerButtonEvent *jb;
        InputEvent::ControllerConnectEvent *jc;

        auto listener = m_listeners.end();
        while (SDL_PollEvent(&evt)) {
            bool eventCreated = true;
            switch (evt.type) {
                case SDL_QUIT:
                    LOG(NG_DEBUG, "Creating Quit type input event");
                    inputEvent.event_type = InputEventType::EVENT_QUIT;
                    inputEvent.event = new InputEvent::QuitEvent;

                    listener = m_listeners.find(InputEventType::EVENT_QUIT);
                    break;
                case SDL_KEYDOWN:
                    LOG(NG_DEBUG, "Creating Key down type input event");
                    LOG(NG_DEBUG, "Key is " + std::to_string(evt.key.keysym.sym));
                    inputEvent.event_type = InputEventType::EVENT_KEYDOWN;
                    kp = new InputEvent::KeyPressEvent;
                    kp->type = InputEventType::EVENT_KEYDOWN;
                    kp->pressed = evt.key.state == SDL_PRESSED;
                    kp->key = (Keys) evt.key.keysym.sym;
                    inputEvent.event = kp;

                    listener = m_listeners.find(InputEventType::EVENT_KEYDOWN);
                    break;
                case SDL_KEYUP:
                    LOG(NG_DEBUG, "Creating Key up type input event");
                    inputEvent.event_type = InputEventType::EVENT_KEYUP;
                    kp = new InputEvent::KeyPressEvent;
                    kp->type = InputEventType::EVENT_KEYUP;
                    kp->pressed = evt.key.state == SDL_PRESSED;
                    kp->key = (Keys) evt.key.keysym.sym;
                    inputEvent.event = kp;

                    listener = m_listeners.find(InputEventType::EVENT_KEYUP);
                    break;
                case SDL_MOUSEMOTION:
                    LOG(NG_DEBUG, "Creating Mouse Motion type input event");
                    inputEvent.event_type = InputEventType::EVENT_MOUSEMOTION;
                    mm = new InputEvent::MouseMotionEvent;
                    mm->type = InputEventType::EVENT_MOUSEMOTION;
                    mm->x_pos = evt.motion.x;
                    mm->y_pos = evt.motion.y;
                    mm->x_pos_relative = evt.motion.xrel;
                    mm->y_pos_relative = evt.motion.yrel;
                    inputEvent.event = mm;

                    listener = m_listeners.find(InputEventType::EVENT_MOUSEMOTION);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    LOG(NG_DEBUG, "Creating Mouse Button down type input event");
                    inputEvent.event_type = InputEventType::EVENT_MOUSEBUTTONDOWN;
                    mb = new InputEvent::MouseButtonEvent;
                    mb->type = InputEventType::EVENT_MOUSEBUTTONDOWN;
                    mb->x_pos = evt.button.x;
                    mb->y_pos = evt.button.y;
                    mb->pressed = evt.button.state == SDL_PRESSED;
                    mb->clicks = evt.button.clicks;
                    inputEvent.event = mb;

                    listener = m_listeners.find(InputEventType::EVENT_MOUSEBUTTONDOWN);
                    break;
                case SDL_MOUSEBUTTONUP:
                    LOG(NG_DEBUG, "Creating Mouse Button up type input event");
                    inputEvent.event_type = InputEventType::EVENT_MOUSEBUTTONUP;
                    mb = new InputEvent::MouseButtonEvent;
                    mb->type = InputEventType::EVENT_MOUSEBUTTONUP;
                    mb->x_pos = evt.button.x;
                    mb->y_pos = evt.button.y;
                    mb->pressed = evt.button.state == SDL_PRESSED;
                    mb->clicks = evt.button.clicks;
                    inputEvent.event = mb;

                    listener = m_listeners.find(InputEventType::EVENT_MOUSEBUTTONUP);
                    break;
                case SDL_MOUSEWHEEL:
                    LOG(NG_DEBUG, "Creating Mouse Wheel type input event");
                    inputEvent.event_type = InputEventType::EVENT_MOUSEWHEEL;
                    mw = new InputEvent::MouseWheelEvent;
                    mw->type = InputEventType::EVENT_MOUSEWHEEL;
                    mw->x_dist = evt.wheel.preciseX;
                    mw->y_dist = evt.wheel.preciseY;
                    inputEvent.event = mw;

                    listener = m_listeners.find(InputEventType::EVENT_MOUSEWHEEL);
                    break;
                case SDL_CONTROLLERAXISMOTION:
                    inputEvent.event_type = InputEventType::EVENT_CONTROLLERJOYSTICK;
                    joy = new InputEvent::ControllerJoystickEvent;
                    joy->type = InputEventType::EVENT_CONTROLLERJOYSTICK;
                    joy->index = evt.caxis.which;
                    joy->axis = evt.caxis.axis;
                    joy->value = evt.caxis.value;
                    inputEvent.event = joy;

                    listener = m_listeners.find(InputEventType::EVENT_CONTROLLERJOYSTICK);
                    break;
                case SDL_CONTROLLERBUTTONDOWN:
                    inputEvent.event_type = InputEventType::EVENT_CONTROLLERBUTTONDOWN;
                    jb = new InputEvent::ControllerButtonEvent;
                    jb->type = InputEventType::EVENT_CONTROLLERBUTTONDOWN;
                    jb->index = evt.cbutton.which;
                    jb->button = evt.cbutton.button;
                    jb->pressed = evt.cbutton.state == SDL_PRESSED;
                    inputEvent.event = jb;

                    listener = m_listeners.find(InputEventType::EVENT_CONTROLLERBUTTONDOWN);
                    break;
                case SDL_CONTROLLERBUTTONUP:
                    inputEvent.event_type = InputEventType::EVENT_CONTROLLERBUTTONUP;
                    jb = new InputEvent::ControllerButtonEvent;
                    jb->type = InputEventType::EVENT_CONTROLLERBUTTONUP;
                    jb->index = evt.cbutton.which;
                    jb->button = evt.cbutton.button;
                    jb->pressed = evt.cbutton.state = SDL_PRESSED;
                    inputEvent.event = jb;

                    listener = m_listeners.find(InputEventType::EVENT_CONTROLLERBUTTONUP);
                    break;
                case SDL_CONTROLLERDEVICEADDED:
                    inputEvent.event_type = InputEventType::EVENT_CONTROLLERCONNECT;
                    jc = new InputEvent::ControllerConnectEvent;
                    jc->type = InputEventType::EVENT_CONTROLLERCONNECT;
                    jc->id = evt.cdevice.which;
                    inputEvent.event = jc;

                    listener = m_listeners.find(InputEventType::EVENT_CONTROLLERCONNECT);
                    break;
                case SDL_CONTROLLERDEVICEREMOVED:
                    inputEvent.event_type = InputEventType::EVENT_CONTROLLERDISCONNECT;
                    jc = new InputEvent::ControllerConnectEvent;
                    jc->type = InputEventType::EVENT_CONTROLLERDISCONNECT;
                    jc->id = evt.cdevice.which;
                    inputEvent.event = jc;

                    listener = m_listeners.find(InputEventType::EVENT_CONTROLLERDISCONNECT);
                    break;
                case SDL_CONTROLLERDEVICEREMAPPED:
                    inputEvent.event_type = InputEventType::EVENT_CONTROLLERREMAP;
                    jc = new InputEvent::ControllerConnectEvent;
                    jc->type = InputEventType::EVENT_CONTROLLERREMAP;
                    jc->id = evt.cdevice.which;
                    inputEvent.event = jc;

                    listener = m_listeners.find(InputEventType::EVENT_CONTROLLERREMAP);
                    break;
                default:
                    eventCreated = false;
                    break;
            }

            if (listener != m_listeners.end() && eventCreated) {
                for (InputListener *l : listener->second) {
                    l->handleEvent(inputEvent);
                }
            }

            if (eventCreated) {
                delete inputEvent.event;
            }
        }
    }

    void InputHandler::addInputListener(InputEventType eventType, InputListener *listener) {
        LOG(NG_DEBUG, "Adding InputListener to InputHandler");
        auto listeners = m_listeners.find(eventType);
        
        if (listeners != m_listeners.end()) {
            LOG(NG_DEBUG, "Found listeners of that type, appending...");
            listeners->second.push_back(listener);
        } else {
            LOG(NG_DEBUG, "No listeners of that type, creating new vector");
            auto newCollection = std::vector<InputListener *>();
            newCollection.push_back(listener);
            m_listeners.insert(std::pair(eventType, newCollection));
        }
    }

    void InputHandler::removeInputListener(InputEventType eventType, InputListener *listener) {
        LOG(NG_DEBUG, "Removing InputListener from InputHandler");
        auto listeners = m_listeners.find(eventType);

        if (listeners == m_listeners.end()) {
            return;
        }

        auto collection = listeners->second;

        for (int i=0; i<collection.size(); ++i) {
            if (collection[i] == listener) {
                LOG(NG_DEBUG, "Removed InputListener");
                collection.erase(collection.begin() + i);
                break;
            }
        }
    }

    bool InputHandler::isEmpty() {
        return m_listeners.empty();
    }
}
