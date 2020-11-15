//
// Created by Jan on 14.11.2020.
//
#include <catch2/catch.hpp>
#include <sceneIO/write/json/JsonSerializer.h>
#include "scene/ShadingNode.h"
#include <sstream>

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
    void connectOutputToInput(const std::string &inputPlugName, PlugPtr outputPlug) override {
        if (inputPlugName == "color") {
            colorPlug.input = static_cast<OutputPlug<Color> *>(outputPlug.getPtr());
        }
    }
    PlugPtr getPlugByName(const std::string &inputPlugName) override {
        if (inputPlugName == "color") {
            return PlugPtr(&colorPlug);
        }
        return {};
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
    void connectOutputToInput(const std::string &inputPlugName, PlugPtr plug) override {
    }
    PlugPtr getPlugByName(const std::string &inputPlugName) override {
        if (inputPlugName == "color") {
            return PlugPtr(&colorPlug);
        }
        return {};
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

TEST_CASE("serialize node") {
    MyMat myMat;
    myMat.setName("MyMat");
    MyFileTextureNode myFileTextureNode;
    myFileTextureNode.setName("MyFileTextureNode");
    myFileTextureNode.colorPlug.connect(&myMat.colorPlug);

    std::shared_ptr<std::ostringstream> px = std::make_shared<std::ostringstream>();
    auto stream = std::shared_ptr<std::ostream>(px);
    JsonSerializer serializer(stream);
    serializer.start();
    serializer.startSceneObjects();

    serializer.startObject();
    myMat.serialize(serializer);
    serializer.endObject();

    serializer.startObject();
    myFileTextureNode.serialize(serializer);
    serializer.endObject();

    serializer.endSceneObjects();
    serializer.end();

    REQUIRE(px->str() == R"({
    "SceneObjects": [
        {
            "name": "MyMat",
            "colorPlug": "MyFileTextureNode.color"
        },
        {
            "name": "MyFileTextureNode"
        }
    ]
})");
}

TEST_CASE("deserialize node") {
    MyMat myMat;
    myMat.generateName();
    MyFileTextureNode myFileTextureNode;
    myFileTextureNode.generateName();
    std::vector<ShadingNode *> nodes({&myMat, &myFileTextureNode});

    auto node = nodes[1]->getPlugByName("color");
    nodes[0]->connectOutputToInput("color", node);

    REQUIRE(myMat.colorPlug.shadingNode == &myMat);
    REQUIRE(myMat.colorPlug.input == &myFileTextureNode.colorPlug);
}
