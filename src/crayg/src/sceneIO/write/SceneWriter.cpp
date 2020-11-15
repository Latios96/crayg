//
// Created by Jan Honsbrok on 01.11.18.
//

#include "SceneWriter.h"

void SceneWriter::write() {
    StopWatch stopwatch = StopWatch::createStopWatch("Scene writing");

    serializerImpl.start();

    serializerImpl.startSceneObjects();
    for (const auto &obj : scene.objects) {
        serializerImpl.startObject();
        obj->serialize(serializerImpl);
        serializerImpl.endObject();
    }
    for (const auto &light : scene.lights) {
        serializerImpl.startObject();
        light->serialize(serializerImpl);
        serializerImpl.endObject();
    }
    for (const auto &material : scene.materials) {
        serializerImpl.startObject();
        material->serialize(serializerImpl);
        serializerImpl.endObject();
    }
    serializerImpl.endSceneObjects();

    if (scene.camera) {
        serializerImpl.startCamera();
        serializerImpl.startObject();
        scene.camera->serialize(serializerImpl);
        serializerImpl.endObject();
        serializerImpl.endCamera();
    }

    serializerImpl.startRenderSettings();
    serializerImpl.startObject();
    serializerImpl.writeInt("width", scene.renderSettings.resolution.getWidth());
    serializerImpl.writeInt("height", scene.renderSettings.resolution.getHeight());
    serializerImpl.writeInt("maxSamples", scene.renderSettings.maxSamples);
    serializerImpl.endObject();
    serializerImpl.endRenderSettings();

    serializerImpl.end();

    stopwatch.end();
};