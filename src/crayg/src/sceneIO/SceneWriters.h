//
// Created by Jan on 16.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_SCENEWRITERS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_SCENEWRITERS_H_

#include <string>
#include <scene/Scene.h>
class SceneWriters {
 public:
    static void writeSceneAsJson(Scene &scene, const std::string &path);
    static void writeSceneAsJson(Scene &scene, std::shared_ptr<std::ostream> stream);
};

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_SCENEWRITERS_H_
