#include <AL/al.h>
#include <AL/alut.h>
#include <content/content_loader.hpp>
#include <content/content_types.hpp>
#include <fstream>
#include <utils/logger.hpp>

#define WAV_HEADER_SIZE 44

namespace Nightingale::Content {
    // this works for mono sound
    struct WavData {
        std::vector<char> data;
        unsigned int sampleRate;
        unsigned short numChannels;
        unsigned short bitsPerSample;
    };

    template<>
    Music ContentLoader::loadContent<Music>(const std::string &filepath) {
        auto it = m_musicCache.find(filepath);

        if (it != m_musicCache.end()) {
            return it->second;
        }

        Music m;

        std::ifstream file(filepath, std::ios::binary);
        if (!file.is_open()) {
            LOG(NG_ERROR, "Failed to open file: " + filepath);
        }

        WavData data;

        char header[WAV_HEADER_SIZE];
        file.read(header, WAV_HEADER_SIZE);

        data.sampleRate = *reinterpret_cast<unsigned int*>(&header[24]);
        data.numChannels = *reinterpret_cast<unsigned short *>(&header[22]);
        data.bitsPerSample = *reinterpret_cast<unsigned short *>(&header[34]);

        file.seekg(WAV_HEADER_SIZE, std::ios::end);
        auto fileSize = file.tellg();
        data.data.resize(fileSize);
        file.seekg(WAV_HEADER_SIZE);
        file.read(data.data.data(), data.data.size());

        file.close();

        if (data.data.empty()) {
            LOG(NG_ERROR, "Data unable to load from file: " + filepath);
        }

        ALenum format;
        if (data.numChannels == 1) {
            format = (data.bitsPerSample == 16) ? AL_FORMAT_MONO16 : AL_FORMAT_MONO8;
        } else if (data.numChannels == 2) {
            format = (data.bitsPerSample == 16) ? AL_FORMAT_STEREO16 : AL_FORMAT_STEREO8;
        } else {
            LOG(NG_ERROR, "Read Unsupported (" + std::to_string(data.numChannels) + ") Number of channels from file: " + filepath);
        }

        alGenBuffers(1, &(m.m_bufferId));

        alBufferData(m.m_bufferId, AL_FORMAT_MONO16, data.data.data(), data.data.size(), data.sampleRate);

        alGenSources(1, &(m.m_sourceId));

        alSourcei(m.m_sourceId, AL_BUFFER, m.m_bufferId);

        LOG(NG_DEBUG, "Music item created; Buffer: " + std::to_string(m.m_bufferId) + ", Source: " + std::to_string(m.m_sourceId));

        return m;
    }

    std::uint32_t Music::getSourceId() {
        return m_sourceId;
    }

    std::uint32_t Music::getBufferId() {
        return m_bufferId;
    }
}
