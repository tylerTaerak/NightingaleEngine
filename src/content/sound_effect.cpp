#include <content/content_loader.hpp>
#include <content/content_types.hpp>
#include <AL/al.h>
#include <AL/alut.h>

namespace Nightingale::Content {
    template<>
    SoundEffect ContentLoader::loadContent<SoundEffect>(const std::string &filepath) {
        auto it = m_soundCache.find(filepath);

        if (it != m_soundCache.end()) {
            return it->second;
        }

        SoundEffect m;

        alGenSources(1, &(m.m_sourceId));

        m.m_bufferId = alutCreateBufferFromFile(filepath.c_str());

        alSourcei(m.m_sourceId, AL_BUFFER, m.m_bufferId);

        return m;
    }

    std::uint32_t SoundEffect::getSourceId() {
        return m_sourceId;
    }

    std::uint32_t SoundEffect::getBufferId() {
        return m_bufferId;
    }
}
