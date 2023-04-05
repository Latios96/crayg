#include "scene/camera/lensio/LensFileReader.h"
#include <catch2/catch.hpp>

namespace crayg {

class DummyLensFileReader : public LensFileReader {
  public:
    explicit DummyLensFileReader(const std::string &filePath) : LensFileReader(filePath) {
    }

    std::vector<LensElement> readFileContent(const std::string &content) override {
        return {};
    }
};

TEST_CASE("TestLensFileReader::readFile") {

    SECTION("should throw if file does not exist") {
        DummyLensFileReader dummyLensFileReader("not-existing-file.txt");

        REQUIRE_THROWS_AS(dummyLensFileReader.readFile(), std::runtime_error);
    }
}

}