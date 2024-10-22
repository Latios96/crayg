#include "TextureStats.h"
#include <OpenImageIO/imagecache.h>

namespace crayg {

std::string TextureStats::getTextureStats() {
    auto imageCache = OIIO::ImageCache::create(true);
    return imageCache->getstats();
}
}