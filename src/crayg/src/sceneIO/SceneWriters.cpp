//
// Created by Jan on 16.11.2020.
//

#include "SceneWriters.h"
#include <fstream>
#include <memory>
#include <utility>
#include <sceneIO/write/json/JsonSerializer.h>
#include <sceneIO/write/SceneWriter.h>
void SceneWriters::writeSceneAsJson(Scene &scene, std::shared_ptr<std::ostream> stream) {
    JsonSerializer jsonSerializer(std::move(stream));
    SceneWriter sceneWriter(scene, jsonSerializer);
    sceneWriter.write();
}
void SceneWriters::writeSceneAsJson(Scene &scene, const std::string &path) {
    std::shared_ptr<std::ofstream> stream = std::make_shared<std::ofstream>(path);
    SceneWriters::writeSceneAsJson(scene, stream);
    stream->close();
}
