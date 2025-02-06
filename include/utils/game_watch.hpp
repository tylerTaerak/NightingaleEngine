#pragma once

#include <cstddef>
namespace Nightingale::Utils {
    static const int NUM_FRAME_SAMPLES = 25;
    class GameWatch {
        public:
            GameWatch();
            ~GameWatch();

            void tick();

            float getFrameTime();

            float getTotalTime();

            float getFramesPerSecond();
        private:
            float m_frameTime;
            float m_totalTime;

            float m_frameTimes[NUM_FRAME_SAMPLES];
            std::size_t m_nextFrameIndex;
    };
}
