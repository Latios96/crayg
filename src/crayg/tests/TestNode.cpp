//
// Created by Jan on 14.11.2020.
//
#include <catch2/catch.hpp>
#include "scene/ShadingNode.h"

class MyMat : public ShadingNode {
 public:
    Plug<Color, INPUT_PLUG> colorPlug;
    MyMat() : colorPlug(Plug<Color, INPUT_PLUG>("color", this, Color::createBlack())) {
    }
    void deserialize(Deserializer &deserializer) override {

    }
    void serialize(Serializer &serializer) override {
        ShadingNode::serialize(serializer);
        if (colorPlug.input) {
            serializer.writeString("colorPlug", colorPlug.input->fullName());
        }
    }
};

class MyFileTextureNode : public ShadingNode {
 public:
    Plug<Color, OUTPUT_PLUG> colorPlug;
    MyFileTextureNode() : colorPlug(Plug<Color, OUTPUT_PLUG>("color", this, Color::createBlack())) {
    }
    void deserialize(Deserializer &deserializer) override {

    }
    void serialize(Serializer &serializer) override {
        ShadingNode::serialize(serializer);
        if (colorPlug.input) {
            serializer.writeString("colorPlug", colorPlug.input->fullName());
        }
    }
};

TEST_CASE("construct network by connecting input to output") {
    MyMat myMat;
    MyFileTextureNode myFileTextureNode;

    myMat.colorPlug.connect(&myFileTextureNode.colorPlug);

    REQUIRE(myMat.colorPlug.shadingNode == &myMat);
    REQUIRE(myMat.colorPlug.input == &myFileTextureNode.colorPlug);
}

TEST_CASE("construct network by connecting output to input") {
    MyMat myMat;
    MyFileTextureNode myFileTextureNode;

    myFileTextureNode.colorPlug.connectTo(&myMat.colorPlug);

    REQUIRE(myMat.colorPlug.shadingNode == &myMat);
    REQUIRE(myMat.colorPlug.input == &myFileTextureNode.colorPlug);
}
