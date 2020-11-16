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
#include "CLI/CLI.hpp"

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

    std::shared_ptr<TriangleMesh> mesh = std::make_shared<TriangleMesh>();
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

    // copy points to mesh
    for (int i = 0; i < attrib.vertices.size() / 3; i++) {
        float x = attrib.vertices[i * 3] - 3;
        float y = attrib.vertices[i * 3 + 1];
        float z = attrib.vertices[i * 3 + 2];
        mesh->points.emplace_back(x, y, z);
    }

    // copy face and uv indices
    for (auto &shape : shapes) {
        for (auto &indice : shape.mesh.indices) {
            mesh->faceIndexes.push_back(indice.vertex_index);
        }
    }
    spdlog::info("Mesh has {} triangles", mesh->faceIndexes.size() / 3);

    Scene scene;
    scene.addObject(mesh);

    std::shared_ptr<std::ofstream> stream = std::make_shared<std::ofstream>(scenePath);
    JsonSerializer jsonSerializer(stream);
    SceneWriter sceneWriter(scene, jsonSerializer);
    sceneWriter.write();
    stream->close();
    return 0;
}