//
// Created by Jan Honsbrok on 23.05.20.
//

#include <iostream>
#include <tiny_obj_loader.h>
#include <spdlog/spdlog.h>
#include <fstream>
#include <scene/TriangleMesh.h>
#include <scene/Scene.h>
#include <sceneIO/SceneWriterFactory.h>

int main() {
    // TODO cli
    std::shared_ptr<TriangleMesh> mesh = std::make_shared<TriangleMesh>();
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;
    std::string path = "/Users/jan/workspace/crayg/cube.obj";
    std::ifstream inputStream(path);

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &inputStream);

    if (!warn.empty()) {
        spdlog::warn(warn);
    }

    if (!err.empty()) {
        spdlog::error(err);
    }

    if (!ret) {
        spdlog::error("Error when reading obj file {}, exiting", path);
        exit(1);
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

    const std::shared_ptr<SceneWriterFacade> sceneWriter = SceneWriterFactory::createSceneWriter("test.json", scene);
    sceneWriter->write();
    return 0;
}