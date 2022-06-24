#ifndef CRAYG_SCENEREADERFACTORY_H
#define CRAYG_SCENEREADERFACTORY_H

#include <memory>
#include <sceneIO/read/SceneReader.h>

namespace crayg {

class SceneReaderFactory {
 public:
    static std::shared_ptr<SceneReader> createSceneReader(std::string scenePath,
                                                          Scene &scene,
                                                          const SceneReader::ReadOptions &readOptions = SceneReader::ReadOptions::empty());
};

}

#endif //CRAYG_SCENEREADERFACTORY_H
