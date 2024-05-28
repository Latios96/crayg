#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNETWORKS_SHADINGNODES_FILETEXTURE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNETWORKS_SHADINGNODES_FILETEXTURE_H_

#include "scene/shadingnetworks/ShadingNode.h"
#include <OpenImageIO/imagecache.h>
#include <OpenImageIO/texture.h>
#include <atomic>

namespace crayg {

enum class ColorSpace { RAW, S_RGB };

class FileTexture : public ShadingNode {
  public:
    explicit FileTexture();
    explicit FileTexture(const std::string &name);

    Color fallbackColor;
    ColorSpace colorSpace;
    Vector2fShadingNodeInput uvInput;

    Color evaluateColor(const SurfaceInteraction &surfaceInteraction) override;
    std::string getType() const override;
    ShadingNodeOutputType getOutputType() override;
    const std::string getFilePath() const;
    void setFilePath(const std::string &filePath);
    ~FileTexture() override;

  private:
    OIIO::TextureSystem *textureSystem;
    OIIO::ustring filePath;
    OIIO::ImageCache *imageCache;
    std::atomic<bool> badTexture;
};
} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNETWORKS_SHADINGNODES_FILETEXTURE_H_
