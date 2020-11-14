//
// Created by Jan on 14.11.2020.
//
#include <catch2/catch.hpp>
#include "scene/ShadingNode.h"

class MyMat : public ShadingNode {
 public:
    InputPlug<Color> colorPlug;
    MyMat() : colorPlug(InputPlug<Color>("color", this, Color::createBlack())) {
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
    OutputPlug<Color> colorPlug;
    MyFileTextureNode() : colorPlug(OutputPlug<Color>("color", this, Color::createBlack(), []() {
        return Color::createGrey(0.5);
    })) {
    }
    void deserialize(Deserializer &deserializer) override {

    }
    void serialize(Serializer &serializer) override {
        ShadingNode::serialize(serializer);
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

    myFileTextureNode.colorPlug.connect(&myMat.colorPlug);

    REQUIRE(myMat.colorPlug.shadingNode == &myMat);
    REQUIRE(myMat.colorPlug.input == &myFileTextureNode.colorPlug);
}

TEST_CASE("should use default value") {
    MyMat myMat;
    MyFileTextureNode myFileTextureNode;

    REQUIRE(myMat.colorPlug.compute() == Color::createBlack());
}

TEST_CASE("should use connected node") {
    MyMat myMat;
    MyFileTextureNode myFileTextureNode;

    myFileTextureNode.colorPlug.connect(&myMat.colorPlug);

    REQUIRE(myMat.colorPlug.compute() == Color::createGrey(0.5));
}
