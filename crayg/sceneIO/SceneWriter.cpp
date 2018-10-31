//
// Created by Jan Honsbrok on 30.10.18.
//



#include <fstream>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include "SceneWriter.h"
#include "JsonSerializer.h"

SceneWriter::SceneWriter(Scene &scene) : scene(scene) {}

void SceneWriter::write() {
    std::ofstream ofs("test.json");
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);

    JsonSerializer serializer(writer);
    serializer.init();

    for (const auto &obj : scene.objects){
        serializer.startObject();
        obj->serialize(serializer);
        serializer.endObject();
    }

    serializer.finish();
    ofs.close();
}
