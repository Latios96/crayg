#include "crayg/testfoundation/fixtures/TemporaryDirectory.h"

#include "crayg/scene/camera/realistic/lensio/LensFileWriter.h"
#include <catch2/catch.hpp>
#include <filesystem>

namespace crayg {

class DummyLensFileWriter : public LensFileWriter {
  public:
    std::string writeFileContent(const CameraLens &cameraLens) override {
        return "CONTENT";
    }
};

TEST_CASE("TestLensFileWriter::writeFile") {

    CameraLens cameraLens(CameraLensMetadata("Canon 70-200"), {{1, 2, 3, 4}, {5, 6, 7, 8}});

    SECTION("should throw if folder does not exist") {
        TemporaryDirectory temporaryDirectory;
        DummyLensFileWriter dummyLensFileWriter;

        REQUIRE_THROWS_AS(dummyLensFileWriter.writeFile(temporaryDirectory.getFilePath("foo/bar.txt"), cameraLens),
                          std::runtime_error);
    }

    SECTION("should read file correctly") {
        TemporaryDirectory temporaryDirectory;
        DummyLensFileWriter dummyLensFileWriter;

        dummyLensFileWriter.writeFile(temporaryDirectory.getFilePath("lensfile.txt"), cameraLens);

        REQUIRE(std::filesystem::exists(temporaryDirectory.getFilePath("lensfile.txt")));
    }
}

}