#include "ShadingNode.h"
#include <utility>

namespace crayg {

ShadingNode::ShadingNode() {
}

ShadingNode::ShadingNode(std::string name) : name(std::move(name)) {
}

std::string ShadingNode::getName() const {
    return name;
}

}
