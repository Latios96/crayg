#include "ShadingNode.h"
#include <utility>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace crayg {

ShadingNode::ShadingNode() {
    generateName();
}
ShadingNode::ShadingNode(std::string name) : name(std::move(name)) {}

std::string ShadingNode::getName() const {
    return name;
}
void ShadingNode::generateName() {
    name = boost::uuids::to_string(boost::uuids::random_generator()());
}

}