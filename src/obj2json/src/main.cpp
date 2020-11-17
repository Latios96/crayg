//
// Created by Jan Honsbrok on 23.05.20.
//

#include <iostream>
#include <tiny_obj_loader.h>
#include <spdlog/spdlog.h>
#include <fstream>
#include <scene/TriangleMesh.h>
#include <scene/Scene.h>
#include <sceneIO/write/json/JsonSerializer.h>
#include <sceneIO/write/SceneWriter.h>
#include <sceneIO/SceneWriters.h>
#include <boost/concept_check.hpp>
#include "CLI/CLI.hpp"

void convertShape(const tinyobj::attrib_t &attrib, Scene &scene, const value_type &shape);
int main(int argc, char *argv[]) {
    CLI::App app {"Crayg, an awesome renderer", "Crayg"};

    std::string objPath;
    app.add_option("-o,--obj", objPath, "obj file to render")->required();

    std::string scenePath;
    app.add_option("-s,--scene", scenePath, "Path where converted scene is saved")->required();

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;
    std::ifstream inputStream(objPath);

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &inputStream);

    if (!warn.empty()) {
        spdlog::warn(warn);
    }

    if (!err.empty()) {
        spdlog::error(err);
    }

    if (!ret) {
        spdlog::error("Error when reading obj file {}, exiting", objPath);
        return 1;
    }

    Scene scene;

    for (auto &shape : shapes) {
        convertShape(attrib, scene, shape);
    }

    SceneWriters::writeSceneAsJson(scene, scenePath);
    return 0;
}

void convertShape(const tinyobj::attrib_t &attrib, Scene &scene, const tinyobj::shape_t &shape) {
    std::map<int, int> faceIndexConversion;
    std::shared_ptr<TriangleMesh> mesh = std::make_shared<TriangleMesh>();
    for (auto &indice : shape.mesh.indices) {
        if (faceIndexConversion.find(indice.vertex_index) == faceIndexConversion.end()) {
            mesh->points.emplace_back(attrib.vertices[indice.vertex_index * 3],
                                      attrib.vertices[indice.vertex_index * 3 + 1],
                                      attrib.vertices[indice.vertex_index * 3 + 2]);
            int newIndex = mesh->points.size() - 1;
            mesh->faceIndexes.push_back(newIndex);
            faceIndexConversion[indice.vertex_index] = newIndex;
        } else {
            mesh->faceIndexes.push_back(faceIndexConversion[indice.vertex_index]);
        }
    }
    scene.addObject(mesh);
}
