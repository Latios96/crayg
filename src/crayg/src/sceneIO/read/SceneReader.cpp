#include "SceneReader.h"
#include <utility>

namespace crayg {

SceneReader::SceneReader(std::string path, Scene &scene, const ReadOptions &readOptions)
    : path{std::move(path)}, scene(scene), readOptions(readOptions) {
}

}
