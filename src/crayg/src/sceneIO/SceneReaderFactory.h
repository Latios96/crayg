//
// Created by Jan Honsbrok on 25.11.18.
//

#ifndef CRAYG_SCENEREADERFACTORY_H
#define CRAYG_SCENEREADERFACTORY_H

#include <memory>
#include <sceneIO/read/SceneReader.h>
#include <sceneIO/read/json/JsonSceneReader.h>

class SceneReaderFactory {
public:
public:
    static std::shared_ptr<SceneReader> createSceneWriter(std::string scenePath, Scene &scene);
};


#endif //CRAYG_SCENEREADERFACTORY_H
