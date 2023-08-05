#ifndef CRAYG_SCENEREADER_H
#define CRAYG_SCENEREADER_H

#include "scene/primitives/trianglemesh/TriangleMesh.h"
#include <optional>
#include <scene/Scene.h>
#include <vector>

namespace crayg {

class SceneReader {
  public:
    struct VariantSelection {
        std::string primPath;
        std::string variantSetName;
        std::string selectedVariant;

        VariantSelection() = default;
        VariantSelection(const std::string &primPath, const std::string &variantSetName,
                         const std::string &selectedVariant);
        bool operator==(const VariantSelection &rhs) const;
        bool operator!=(const VariantSelection &rhs) const;
    };

    struct ReadOptions {
        std::optional<std::string> cameraName;
        std::vector<VariantSelection> variantSelections;

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
