#include "al.h"
#include <utils/logger.hpp>
#include <algorithm>
#include <audio/audio_player.hpp>

namespace Nightingale::Audio {
    ALenum error;

    AudioPlayer::AudioPlayer() {
        m_device = alcOpenDevice(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

        if (!m_device) {
            LOG(NG_DEBUG, "Error Opening Audio Device");
        }

        m_context = alcCreateContext(m_device, NULL);

        alcMakeContextCurrent(m_context);

        if ((error = alGetError()) != AL_NO_ERROR) {
            LOG(NG_DEBUG, "OpenAL Error: " + std::to_string(error));
        }

        alListener3f(AL_POSITION, 0.f, 0.f, 0.f);
    }

    AudioPlayer::~AudioPlayer() {
        alcMakeContextCurrent(NULL);

        alcDestroyContext(m_context);

        alcCloseDevice(m_device);
    }

    void AudioPlayer::playMusic(Content::Music &music) {
        if (std::find(m_musicIds.begin(), m_musicIds.end(), music.getSourceId()) != m_musicIds.end()) {
            return;
        }

        LOG(NG_DEBUG, "Music Source ID: " + std::to_string(music.getSourceId()));

        alSourcePlay(music.getSourceId());

        if ((error = alGetError()) != AL_NO_ERROR) {
            LOG(NG_DEBUG, "OpenAL Error: " + std::to_string(error));
        }

        m_musicIds.push_back(music.getSourceId());
    }

    void AudioPlayer::playSoundEffect(Content::SoundEffect &sound) {
        if (std::find(m_soundEffectIds.begin(), m_soundEffectIds.end(), sound.getSourceId()) != m_soundEffectIds.end()) {
            return;
        }

        alSourcePlay(sound.getSourceId());

        if ((error = alGetError()) != AL_NO_ERROR) {
            LOG(NG_DEBUG, "OpenAL Error: " + std::to_string(error));
        }

        m_soundEffectIds.push_back(sound.getSourceId());
    }
}
