#ifndef CRAYG_SCENEREADER_H
#define CRAYG_SCENEREADER_H

#include "scene/primitives/trianglemesh/TriangleMesh.h"
#include <optional>
#include <scene/Scene.h>
#include <vector>

namespace crayg {

CRAYG_DTO_3(SceneReaderVariantSelection, std::string, primPath, std::string, variantSetName, std::string,
            selectedVariant);

class SceneReader {
  public:
    struct ReadOptions {
        std::optional<std::string> cameraName;
        std::vector<SceneReaderVariantSelection> variantSelections;

        static ReadOptions empty() {
            return {};
        }
    };

    virtual void read() = 0;

    explicit SceneReader(std::string path, Scene &scene, const ReadOptions &readOptions = ReadOptions::empty());

  protected:
    Scene &scene;
    std::string path;
    const ReadOptions &readOptions;
};

}

#endif // CRAYG_SCENEREADER_H
