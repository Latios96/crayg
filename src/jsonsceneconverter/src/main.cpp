#include <boost/filesystem/path.hpp>
#include "CLI/CLI.hpp"
#include "sceneIO/SceneReaderFactory.h"
#include "sceneIO/write/usd/UsdSceneWriter.h"

int main(int argc, char *argv[]) {
    CLI::App app {"Json Scene Converter", "JsonSceneConverter"};

    std::string scenePath;
    app.add_option("-i,--input", scenePath, "scene file to convert")->required();

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    crayg::Scene scene;
    auto sceneReader = crayg::SceneReaderFactory::createSceneReader(scenePath, scene);
    sceneReader->read();

    const boost::filesystem::path path = boost::filesystem::path(scenePath);
    std::string targetPath = (path.parent_path() / boost::filesystem::path(path.stem().string() + ".usda")).string();

    crayg::UsdSceneWriter usdSceneWriter;
    usdSceneWriter.writeScene(targetPath, scene);

    return 0;
}