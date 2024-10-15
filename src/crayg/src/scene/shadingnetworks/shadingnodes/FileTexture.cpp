#include "FileTexture.h"
#include "Logger.h"
#include "image/ColorConversion.h"

namespace crayg {
Color FileTexture::evaluateColor(const SurfaceInteraction &surfaceInteraction) {
    if (badTexture) {
        return fallbackColor;
    }

    const Vector2f &uv = uvInput.evaluate(surfaceInteraction);

    float result[3];
    const bool ok = textureSystem->texture(filePath, textureOpt, uv.x, 1 - uv.y, 0, 0, 0, 0, 3, result);

    if (!ok) {
        badTexture = true;
        Logger::error("Could not load texture file {} from {}", filePath, getName());
        return fallbackColor;
    }

    const Color color(result);

    if (colorSpace == ColorSpace::RAW) {
        return color;
    }

    return ColorConversion::sRGBToLinear(color);
}

std::string FileTexture::getType() const {
    return "FileTexture";
}

ShadingNodeOutputType FileTexture::getOutputType() {
    return ShadingNodeOutputType::COLOR;
}

FileTexture::FileTexture() : FileTexture("") {
}

FileTexture::FileTexture(const std::string &name) : ShadingNode(name) {
    imageCache = OIIO::ImageCache::create(true);
    imageCache->attribute("max_memory_MB", 4000.0f);
    textureSystem = OIIO::TextureSystem::create(imageCache);
    textureOpt.swrap = OIIO::TextureOpt::Wrap::WrapPeriodic;
    textureOpt.twrap = OIIO::TextureOpt::Wrap::WrapPeriodic;
}

FileTexture::~FileTexture() {
    OIIO::TextureSystem::destroy(textureSystem);
}

const std::string FileTexture::getFilePath() const {
    return filePath.string();
}

void FileTexture::setFilePath(const std::string &path) {
    filePath = OIIO::ustring(path);
}

} // crayg