#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_SCENEWRITERFACTORY_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_SCENEWRITERFACTORY_H_

#include "sceneIO/write/SceneWriter.h"

namespace crayg {

class SceneWriterFactory {
 public:
    static std::shared_ptr<SceneWriter> createSceneWriter(std::string scenePath, Scene &scene);
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_SCENEWRITERFACTORY_H_
