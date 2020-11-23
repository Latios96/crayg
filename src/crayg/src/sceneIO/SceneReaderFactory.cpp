//
// Created by Jan Honsbrok on 25.11.18.
//


#include "SceneReaderFactory.h"

namespace crayg {

std::shared_ptr<SceneReader> SceneReaderFactory::createSceneWriter(std::string scenePath, Scene &scene) {
    return std::shared_ptr<SceneReader>(new JsonSceneReader(scenePath, scene));
}

}
