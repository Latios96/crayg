#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNETWORKS_SHADINGNODES_FILETEXTURE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNETWORKS_SHADINGNODES_FILETEXTURE_H_

#include "scene/shadingnetworks/ShadingNode.h"
#include <OpenImageIO/imagecache.h>
#include <OpenImageIO/texture.h>
#include <atomic>

namespace crayg {

class FileTexture : public ShadingNode {
  public:
    explicit FileTexture();
    explicit FileTexture(const std::string &name);

    Color fallbackColor;

    enum class ColorSpace { RAW, S_RGB };

    ColorSpace colorSpace;
    Vector2fShadingNodeInput uvInput;

    Color evaluateColor(const SurfaceInteraction &surfaceInteraction) override;
    std::string getType() const override;
    ShadingNodeOutputType getOutputType() override;
    const std::string getFilePath() const;
    void setFilePath(const std::string &filePath);
    ~FileTexture() override;

  private:
    OIIO::TextureSystem *textureSystem = nullptr;
    OIIO::ustring filePath;
    OIIO::ImageCache *imageCache = nullptr;
    std::atomic<bool> badTexture = 0;
    OIIO::TextureOpt textureOpt;
};
} // crayg

CRAYG_FMT_ENUM_FORMATTER(crayg::FileTexture::ColorSpace);

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNETWORKS_SHADINGNODES_FILETEXTURE_H_
