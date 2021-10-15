//
// Created by Jan Honsbrok on 25.11.18.
//

#ifndef CRAYG_JSONSCENEREADER_H
#define CRAYG_JSONSCENEREADER_H

static const char *const SCENE_OBJECTS = "SceneObjects";
static const char *const CAMERA = "Camera";
static const char *const RENDER_SETTINGS = "RenderSettings";

#include <sceneIO/read/SceneReader.h>

namespace crayg {

class SceneObjectsMissing : public std::exception {
    const char *what() const noexcept override {
        return "\"SceneObjects\" key is missing!";
    }
};

class CameraIsMissing : public std::exception {
    const char *what() const noexcept override {
        return "Camera is missing!";
    }
};

class SceneObjectsIsNotArray : public std::exception {
    const char *what() const noexcept override {
        return "Value at \"SceneObjects\" key is not an array!";
    }
};
class RenderSettingsAreMissing : public std::exception {
    const char *what() const noexcept override {
        return "Scene contains no RenderSettings!";
    }
};

class JsonSceneReader : public SceneReader {
 public:
    JsonSceneReader(const std::string &path, Scene &scene);

    void read() override;
    void readFromStream(std::istream &ifs) const;
};

}

#endif //CRAYG_JSONSCENEREADER_H
