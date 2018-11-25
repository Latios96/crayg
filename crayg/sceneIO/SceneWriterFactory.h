//
// Created by Jan Honsbrok on 25.11.18.
//

#ifndef CRAYG_SCENEWRITERFACTORY_H
#define CRAYG_SCENEWRITERFACTORY_H

#include <string>
#include "sceneIO/write/SceneWriter.h"

class SceneWriterFactory {
    static std::shared_ptr<SceneWriter> createSceneWriter(std::string scenePath);
};


#endif //CRAYG_SCENEWRITERFACTORY_H
