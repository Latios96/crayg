//
// Created by Jan Honsbrok on 25.11.18.
//

#include "SceneWriterFactory.h"

SceneWriterFacade::SceneWriterFacade(SceneWriter *writer,
                                     SerializerImplementation *serializerImplementation) : writer(writer),
                                                                                           serializerImplementation(
                                                                                               serializerImplementation) {}

SceneWriterFacade::~SceneWriterFacade() {
    delete writer;
    delete serializerImplementation;
}

void SceneWriterFacade::write() {
    writer->write();
}

std::shared_ptr<SceneWriterFacade> SceneWriterFactory::createSceneWriter(std::string scenePath, Scene &scene) {
    SerializerImplementation *impl = new JsonSerializer(scenePath);
    SceneWriter *writer = new SceneWriter(scene, *impl);
    return std::shared_ptr<SceneWriterFacade>(new SceneWriterFacade(writer, impl));
}
