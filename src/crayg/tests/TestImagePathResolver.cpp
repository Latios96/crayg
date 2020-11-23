//
// Created by Jan on 23.11.2020.
//
#include <catch2/catch.hpp>
#include <ImagePathResolver.h>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

class FileFixture {
 public:
    explicit FileFixture(const boost::filesystem::path &path) : path(path) {
        const boost::filesystem::path folder = path.parent_path();
        if (!folder.empty()) {
            boost::filesystem::create_directories(folder);
        }
        std::ofstream outfile(path.string());
        outfile.close();
    }
    ~FileFixture() {
        boost::filesystem::remove(path);
    }
 private:
    boost::filesystem::path path;
};

TEST_CASE("ImagePathResolver should replace #") {

    ImagePathResolver imagePathResolver;

    SECTION("no # should not change") {
        FileFixture fileFixture("test.1000.png");

        std::string result = imagePathResolver.resolve("test.1000.png");

        REQUIRE(result == "test.1000.png");
    }

    SECTION("not existing before") {
        std::string result = imagePathResolver.resolve("test.#.png");

        REQUIRE(result == "test.0001.png");
    }

    SECTION("existing file") {
        FileFixture fileFixture("test.0001.png");

        std::string result = imagePathResolver.resolve("test.#.png");

        REQUIRE(result == "test.0002.png");
    }
}

TEST_CASE("ImagePathResolver shouldParseImageNumber") {
    ImagePathResolver imagePathResolver;

    SECTION("1001") {
        int frameNumber = imagePathResolver.parseImageNumber("test.1001.png");
        REQUIRE(frameNumber == 1001);
    }

    SECTION("0001") {
        int frameNumber = imagePathResolver.parseImageNumber("test.0001.png");
        REQUIRE(frameNumber == 0001);
    }

    SECTION("0000") {
        int frameNumber = imagePathResolver.parseImageNumber("test.0000.png");
        REQUIRE(frameNumber == 0000);
    }

    SECTION("-1") {
        int frameNumber = imagePathResolver.parseImageNumber("test.png");
        REQUIRE(frameNumber == -1);
    }

}
