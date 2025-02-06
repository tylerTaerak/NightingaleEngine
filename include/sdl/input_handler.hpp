#pragma once

#include "nightingale_typedefs.hpp"
#include <vector>
#include <map>

namespace Nightingale::SDL {

    class InputListener {
        public:
            virtual void handleEvent(const InputEvent &evt) = 0;
        private:
    };


    class InputHandler {
        public:
            InputHandler();

            ~InputHandler();

            void processInput();

            void addInputListener(InputEventType eventType, InputListener *listener);

            void removeInputListener(InputEventType eventType, InputListener *listener);

            bool isEmpty();

        private:
            std::map<InputEventType, std::vector<InputListener *>> m_listeners;
    };
}
