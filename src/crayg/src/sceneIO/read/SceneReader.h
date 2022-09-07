#ifndef CRAYG_SCENEREADER_H
#define CRAYG_SCENEREADER_H

#include <scene/Scene.h>
#include <optional>
#include "scene/primitives/trianglemesh/TriangleMesh.h"

namespace crayg {

class SceneReader {
 public:

    struct ReadOptions {
        std::optional<std::string> cameraName;
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

#endif //CRAYG_SCENEREADER_H
