#include <boost/regex.hpp>
#include <catch2/catch.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <utils/ImagePathResolver.h>

namespace crayg {

class FileFixture {
  public:
    explicit FileFixture(const std::filesystem::path &path) : path(path) {
        const std::filesystem::path folder = path.parent_path();
        if (!folder.empty()) {
            std::filesystem::create_directories(folder);
        }
        std::ofstream outfile(path.string());
        outfile.close();
    }

    ~FileFixture() {
        std::filesystem::remove(path);
    }

  private:
    std::filesystem::path path;
};

TEST_CASE("ImagePathResolver should replace #") {

    ImagePathResolver imagePathResolver;

    SECTION("no # should not change") {
        FileFixture fileFixture("1203e5c176ab4e7fbe124ae4258131b4.1000.png");

        const std::filesystem::path result = imagePathResolver.resolve("1203e5c176ab4e7fbe124ae4258131b4.1000.png");

        REQUIRE(result == "1203e5c176ab4e7fbe124ae4258131b4.1000.png");
    }

    SECTION("not existing before") {
        const std::filesystem::path result = imagePathResolver.resolve("1203e5c176ab4e7fbe124ae4258131b4.#.png");

        REQUIRE(result == "1203e5c176ab4e7fbe124ae4258131b4.0001.png");
    }

    SECTION("existing file") {
        FileFixture fileFixture("1203e5c176ab4e7fbe124ae4258131b4.0001.png");

        const std::filesystem::path result = imagePathResolver.resolve("1203e5c176ab4e7fbe124ae4258131b4.#.png");

        REQUIRE(result == "1203e5c176ab4e7fbe124ae4258131b4.0002.png");
    }
}

TEST_CASE("ImagePathResolver::parseImageNumber") {
    ImagePathResolver imagePathResolver;

    SECTION("should parse '1001'") {
        int frameNumber = imagePathResolver.parseImageNumber("1203e5c176ab4e7fbe124ae4258131b4.1001.png");
        REQUIRE(frameNumber == 1001);
    }

    SECTION("should parse '0001'") {
        int frameNumber = imagePathResolver.parseImageNumber("1203e5c176ab4e7fbe124ae4258131b4.0001.png");
        REQUIRE(frameNumber == 0001);
    }

    SECTION("should parse '0000'") {
        int frameNumber = imagePathResolver.parseImageNumber("1203e5c176ab4e7fbe124ae4258131b4.0000.png");
        REQUIRE(frameNumber == 0000);
    }

    SECTION("should parse '-1'") {
        int frameNumber = imagePathResolver.parseImageNumber("1203e5c176ab4e7fbe124ae4258131b4.png");
        REQUIRE(frameNumber == -1);
    }
}

TEST_CASE("ImagePathResolver::matchesTemplate") {
    ImagePathResolver imagePathResolver;

    REQUIRE(imagePathResolver.matchesTemplate("1203e5c176ab4e7fbe124ae4258131b4.#.png",
                                              "1203e5c176ab4e7fbe124ae4258131b4.1.png"));
    REQUIRE(imagePathResolver.matchesTemplate("1203e5c176ab4e7fbe124ae4258131b4.#.png",
                                              "1203e5c176ab4e7fbe124ae4258131b4.1000.png"));
    REQUIRE(imagePathResolver.matchesTemplate("1203e5c176ab4e7fbe124ae4258131b4.#.png",
                                              "1203e5c176ab4e7fbe124ae4258131b4.0001.png"));
    REQUIRE_FALSE(imagePathResolver.matchesTemplate("1203e5c176ab4e7fbe124ae4258131b4.1000.png",
                                                    "1203e5c176ab4e7fbe124ae4258131b4.0001.png"));
    REQUIRE_FALSE(imagePathResolver.matchesTemplate("tt.png", "1203e5c176ab4e7fbe124ae4258131b4.0001.png"));
}

}
