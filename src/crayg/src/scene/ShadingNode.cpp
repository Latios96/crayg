//
// Created by Jan on 14.11.2020.
//

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
void ShadingNode::serialize(Serializer &serializer) {
    serializer.writeString("name", name);
}
void ShadingNode::deserialize(Deserializer &deserializer) {
    name = deserializer.readString("name");
}

}
