#include "SDL_timer.h"
#include <utils/game_watch.hpp>

namespace Nightingale::Utils {
    GameWatch::GameWatch() 
        : m_frameTime(0.f), m_totalTime(0.f) {
    }

    GameWatch::~GameWatch() {
    }

    void GameWatch::tick() {
        m_frameTime = SDL_GetTicks() - m_totalTime;
        m_totalTime += m_frameTime;

        m_frameTimes[m_nextFrameIndex++ % NUM_FRAME_SAMPLES] = m_frameTime;
    }

    float GameWatch::getFrameTime() {
        return m_frameTime;
    }

    float GameWatch::getTotalTime() {
        return m_totalTime;
    }

    float GameWatch::getFramesPerSecond() {
        int count;
        if (m_nextFrameIndex < NUM_FRAME_SAMPLES) {
            count = m_nextFrameIndex;
        } else {
            count = NUM_FRAME_SAMPLES;
        }

        float frameAverage = 0.f;
        for (int i=0; i<count; i++) {
            frameAverage += m_frameTimes[i];
        }

        frameAverage /= count;

        if (frameAverage > 0) {
            return 1000 / frameAverage;
        }

        return 60.f;
    }
}
