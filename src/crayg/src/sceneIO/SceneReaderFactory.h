//
// Created by Jan Honsbrok on 25.11.18.
//

#ifndef CRAYG_SCENEREADERFACTORY_H
#define CRAYG_SCENEREADERFACTORY_H

#include <memory>
#include <sceneIO/read/SceneReader.h>
#include <sceneIO/read/json/JsonSceneReader.h>

namespace crayg {

class SceneReaderFactory {
 public:
 public:
    static std::shared_ptr<SceneReader> createSceneReader(std::string scenePath,
                                                          Scene &scene,
                                                          const SceneReader::ReadOptions &readOptions = SceneReader::ReadOptions::empty());
};

}

#endif //CRAYG_SCENEREADERFACTORY_H
