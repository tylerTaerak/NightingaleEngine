#include <content/content_loader.hpp>
#include <utils/logger.hpp>

#include <SDL_image.h>

namespace Nightingale::Content {
    ContentLoader::ContentLoader() {
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        FT_Init_FreeType(&m_library);
        LOG(NG_DEBUG, "Freetype initialized");

        int major;
        int minor;
        int patch;

        FT_Library_Version(m_library, &major, &minor, &patch);

        LOG(NG_DEBUG, "Loaded Freetype Library Version: " + std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch));
    }

    ContentLoader::~ContentLoader() {
        IMG_Quit();
        FT_Done_FreeType(m_library);
    }
}
