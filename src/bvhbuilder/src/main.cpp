#include <iostream>
#include <tiny_obj_loader.h>
#include <spdlog/spdlog.h>
#include <scene/TriangleMesh.h>
#include <scene/Scene.h>
#include <sceneIO/SceneReaderFactory.h>
#include "CLI/CLI.hpp"
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <utils/StopWatch.h>
#include <intersectors/BvhBuilder.h>

void write(rapidjson::Writer<rapidjson::OStreamWrapper> &writer, const crayg::BvhNode &tree) {
    writer.StartObject();
    writer.Key("bounds");
    writer.StartArray();
    writer.Double(tree.boundingBox.min.x);
    writer.Double(tree.boundingBox.min.y);
    writer.Double(tree.boundingBox.min.z);
    writer.Double(tree.boundingBox.max.x);
    writer.Double(tree.boundingBox.max.y);
    writer.Double(tree.boundingBox.max.z);
    writer.EndArray();
    writer.Key("left");
    if (tree.left != nullptr) {
        write(writer, *tree.left);
    } else {
        writer.Null();
    }
    writer.Key("right");
    if (tree.right != nullptr) {
        write(writer, *tree.right);
    } else {
        writer.Null();
    }
    writer.EndObject();
}

void writeTree(const std::string &path, const crayg::BvhNode &tree) {
    std::ofstream stream = std::ofstream(path);
    rapidjson::OStreamWrapper osw(stream);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);

    write(writer, tree);

    stream.close();
}

int main(int argc, char *argv[]) {
    CLI::App app {"BVH Builder", "BVH Builder"};

    std::string bvhOutput;
    app.add_option("-o,--bvhOutput", bvhOutput, "Path to put the BVH File to")->required();

    std::string scenePath;
    app.add_option("-s,--scene", scenePath, "Path of the scene to create the BVH for")->required();

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    crayg::Scene scene;

    auto sceneReader = crayg::SceneReaderFactory::createSceneReader(scenePath, scene);
    sceneReader->read();

    crayg::StopWatch stopWatch = crayg::StopWatch::createStopWatch("building BVH");

    crayg::BvhBuilder bvhBuilder(scene);
    std::unique_ptr<crayg::BvhNode> root = std::unique_ptr<crayg::BvhNode>(bvhBuilder.build());

    stopWatch.end();

    crayg::StopWatch stopWatchWrite = crayg::StopWatch::createStopWatch("writing BVH");
    writeTree(bvhOutput, *root);
    stopWatchWrite.end();

    return 0;
}

