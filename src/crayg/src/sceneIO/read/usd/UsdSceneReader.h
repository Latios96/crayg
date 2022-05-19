//
// Created by Jan Honsbrok on 25.11.18.
//

#ifndef CRAYG_USDSCENEREADER_H
#define CRAYG_USDSCENEREADER_H

#include "sceneIO/read/SceneReader.h"

namespace crayg {

class UsdSceneReader : public SceneReader {
 public:
    UsdSceneReader(const std::string &path, Scene &scene);

    void read() override;
};

}

#endif //CRAYG_USDSCENEREADER_H
