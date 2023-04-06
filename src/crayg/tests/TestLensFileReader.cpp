#include "fixtures/TemporaryDirectory.h"
#include "scene/camera/lensio/LensFileReader.h"
#include <catch2/catch.hpp>

namespace crayg {

class DummyLensFileReader : public LensFileReader {
  public:
    explicit DummyLensFileReader(const std::string &filePath) : LensFileReader(filePath) {
    }

    CameraLens readFileContent(const std::string &content) override {
        return {"", std::vector<LensElement>({{1, 2, 3, 4}, {5, 6, 7, 8}})};
    }
};

TEST_CASE("TestLensFileReader::readFile") {

    SECTION("should throw if file does not exist") {
        DummyLensFileReader dummyLensFileReader("not-existing-file.txt");

        REQUIRE_THROWS_AS(dummyLensFileReader.readFile(), std::runtime_error);
    }

    SECTION("should read file correctly") {
        TemporaryDirectory temporaryDirectory;
        auto filePath = temporaryDirectory.writeToFile("testfile.txt", R"(# a header comment
3
1 2 3 4
5 6 7 8)");
        DummyLensFileReader dummyLensFileReader(filePath);

        auto cameraLens = dummyLensFileReader.readFile();

        REQUIRE(cameraLens == CameraLens("", std::vector<LensElement>({{1, 2, 3, 4}, {5, 6, 7, 8}})));
    }
}

}