//
// Created by Jan Honsbrok on 25.11.18.
//

#ifndef CRAYG_SCENEWRITERFACTORY_H
#define CRAYG_SCENEWRITERFACTORY_H

#include <string>
#include <memory>
#include "sceneIO/write/SceneWriter.h"

class SceneWriterFacade{
public:
    SceneWriterFacade(SceneWriter *writer, SerializerImplementation *serializerImplementation);
    
    void write();
    
    virtual ~SceneWriterFacade();

private:
    SceneWriter *writer;
    SerializerImplementation *serializerImplementation;
};

class SceneWriterFactory {
public:
    static std::shared_ptr<SceneWriterFacade> createSceneWriter(std::string scenePath, Scene &scene);
};


#endif //CRAYG_SCENEWRITERFACTORY_H
