#include "SceneReader.h"
#include <utility>

namespace crayg {

SceneReader::SceneReader(std::string path, Scene &scene, const ReadOptions &readOptions)
    : path{std::move(path)}, scene(scene), readOptions(readOptions) {
}

bool SceneReader::VariantSelection::operator==(const SceneReader::VariantSelection &rhs) const {
    return primPath == rhs.primPath && variantSetName == rhs.variantSetName && selectedVariant == rhs.selectedVariant;
}

bool SceneReader::VariantSelection::operator!=(const SceneReader::VariantSelection &rhs) const {
    return !(rhs == *this);
}

SceneReader::VariantSelection::VariantSelection(const std::string &primPath, const std::string &variantSetName,
                                                const std::string &selectedVariant)
    : primPath(primPath), variantSetName(variantSetName), selectedVariant(selectedVariant) {
}
}
