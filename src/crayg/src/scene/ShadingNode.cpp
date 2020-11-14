//
// Created by Jan on 14.11.2020.
//

#include "ShadingNode.h"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

const std::string &ShadingNode::getName() const {
    return name;
}
void ShadingNode::setName(const std::string &name) {
    ShadingNode::name = name;
}
void ShadingNode::generateName() {
    name = boost::uuids::to_string(boost::uuids::random_generator()());
}
void ShadingNode::serialize(Serializer &serializer) {
    serializer.writeString("name", name);
}
