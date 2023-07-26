#include "fixtures/TemporaryDirectory.h"
#include "scene/camera/lensio/LensFileWriter.h"
#include <catch2/catch.hpp>

namespace crayg {

class DummyLensFileWriter : public LensFileWriter {
  public:
    std::string writeFileContent(const CameraLens &cameraLens) override {
        return "CONTENT";
    }
};

TEST_CASE("TestLensFileWriter::readFile") {

    CameraLens cameraLens(CameraLensMetadata("Canon 70-200"), {{1, 2, 3, 4}, {5, 6, 7, 8}});

    SECTION("should throw if file does not exist") {
        DummyLensFileWriter dummyLensFileWriter;

        REQUIRE_THROWS_AS(dummyLensFileWriter.writeFile("not-existing-file.txt", cameraLens), std::runtime_error);
    }

    SECTION("should read file correctly") {
        TemporaryDirectory temporaryDirectory;
        DummyLensFileWriter dummyLensFileWriter;

        dummyLensFileWriter.writeFile(temporaryDirectory.getFilePath("lensfile.txt"), cameraLens);

        REQUIRE(boost::filesystem::exists(temporaryDirectory.getFilePath("lensfile.txt")));
    }
}

}