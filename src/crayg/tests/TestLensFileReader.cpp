#include "fixtures/TemporaryDirectory.h"
#include "scene/camera/lensio/LensFileReader.h"
#include <catch2/catch.hpp>

namespace crayg {

class DummyLensFileReader : public LensFileReader {
  public:
    explicit DummyLensFileReader() = default;

    CameraLens readFileContent(const std::string &content) override {
        return {"", std::vector<LensElement>({{1, 2, 3, 4}, {5, 6, 7, 8}})};
    }
};

TEST_CASE("TestLensFileReader::readFile") {

    SECTION("should throw if file does not exist") {
        DummyLensFileReader dummyLensFileReader;

        REQUIRE_THROWS_AS(dummyLensFileReader.readFile("not-existing-file.txt"), std::runtime_error);
    }

    SECTION("should read file correctly") {
        TemporaryDirectory temporaryDirectory;
        auto filePath = temporaryDirectory.writeToFile("testfile.txt", R"(# a header comment
3
1 2 3 4
5 6 7 8)");
        DummyLensFileReader dummyLensFileReader;

        auto cameraLens = dummyLensFileReader.readFile(filePath);

        REQUIRE(cameraLens == CameraLens("", std::vector<LensElement>({{1, 2, 3, 4}, {5, 6, 7, 8}})));
    }
}

}