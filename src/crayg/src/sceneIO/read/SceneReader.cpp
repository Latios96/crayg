#include <utility>

//
// Created by Jan Honsbrok on 31.10.18.
//

#include "SceneReader.h"

namespace crayg {

SceneReader::SceneReader(std::string path, Scene &scene) : path {std::move(path)}, scene(scene) {
}

}
