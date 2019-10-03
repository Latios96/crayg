//
// Created by jan on 03/10/2019.
//
#include <catch2/catch.hpp>
#include <image/Image.h>
#include <boost/filesystem.hpp>
#include <image/OpenImageIoImageWriter.h>
#include <image/ImageIterators.h>

TEST_CASE("OpenImageIoImageWriter") {
    Image image(20, 10);
    OpenImageIoImageWriter openImageIoImageWriter;

    for (auto p: ImageIterators::lineByLine(image)) {
        image.setValue(p.x, p.y, Color::createGrey(static_cast<float>(p.x) / static_cast<float>(image.getWidth())));
    }

    if (boost::filesystem::exists("OpenImageIoImageWriter.png")) {
        REQUIRE(remove("OpenImageIoImageWriter.png") == 0);
    }

    openImageIoImageWriter.writeImage(image, "OpenImageIoImageWriter.png");
    REQUIRE(boost::filesystem::exists("OpenImageIoImageWriter.png"));

    if (boost::filesystem::exists("testImage.png")) {
        REQUIRE(remove("testImage.png") == 0);
    }
}
