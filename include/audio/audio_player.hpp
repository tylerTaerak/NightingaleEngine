#pragma once

#include "alc.h"
#include "content/content_types.hpp"

namespace Nightingale::Audio {
    class AudioPlayer {
        public:
            AudioPlayer();

            ~AudioPlayer();

            void playMusic(Content::Music &music);

            void playSoundEffect(Content::SoundEffect &sound);
        private:
            std::vector<std::uint32_t> m_musicIds;
            std::vector<std::uint32_t> m_soundEffectIds;

            ALCcontext *m_context;
            ALCdevice *m_device;
    };
}
