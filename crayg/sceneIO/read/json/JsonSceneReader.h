//
// Created by Jan Honsbrok on 25.11.18.
//

#ifndef CRAYG_JSONSCENEREADER_H
#define CRAYG_JSONSCENEREADER_H

static const char *const SCENE_OBJECTS = "SceneObjects";
static const char *const CAMERA = "Camera";

#include <sceneIO/read/SceneReader.h>

// todo add tests
// todo make more robust with error messages
class JsonSceneReader : public SceneReader{
public:
    JsonSceneReader(const std::string &path, Scene &scene);

    void read() override;
};


#endif //CRAYG_JSONSCENEREADER_H
