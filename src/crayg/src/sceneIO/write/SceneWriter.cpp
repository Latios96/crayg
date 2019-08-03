//
// Created by Jan Honsbrok on 01.11.18.
//

#include "SceneWriter.h"

void SceneWriter::write() {
    StopWatch stopwatch = StopWatch::createStopWatch("Scene writing");

    serializerImpl.init();

    for (const auto &obj : scene.objects){
        serializerImpl.startObject();
        obj->serialize(serializerImpl);
        serializerImpl.endObject();
    }
    if(scene.camera){
        serializerImpl.startObject();
        scene.camera->serialize(serializerImpl);
        serializerImpl.endObject();
    }

    serializerImpl.finish();

    stopwatch.end();
};