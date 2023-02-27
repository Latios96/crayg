#include <catch2/catch.hpp>
#include <image/Image.h>

namespace crayg {

TEST_CASE("Image/constructImage", "[Image]") {
    Image myImage(200, 100);

    REQUIRE(myImage.getWidth() == 200);
    REQUIRE(myImage.getHeight() == 100);

    REQUIRE(myImage.rgb.isBlack());
    REQUIRE(myImage.channelNames() == std::vector<std::string_view>({"rgb"}));
}

TEST_CASE("Image/copyImage", "[Image]") {
    SECTION("copy image with rgb") {
        Image myImage(200, 100);

        for (int x = 0; x < myImage.getWidth(); x++) {
            for (int y = 0; y < myImage.getHeight(); y++) {
                myImage.setValue(x, y, Color::createGrey(static_cast<float>(x) * static_cast<float>(y)));
            }
        }

        Image otherImage(myImage);

        REQUIRE(myImage == otherImage);
    }

    SECTION("copy images with channels") {
        Image myImage(200, 100);
        myImage.addAlphaChannel();

        Image otherImage(myImage);

        REQUIRE(myImage == otherImage);
        REQUIRE(otherImage.hasAlphaChannel());
    }
}

TEST_CASE("Image/addAlphaChannel", "[Image]") {
    SECTION("should add alpha channel") {
        Image myImage(16, 9);

        myImage.addAlphaChannel();

        REQUIRE(myImage.channelNames() == std::vector<std::string_view>({"rgb", "alpha"}));
        REQUIRE(myImage.hasAlphaChannel());
        REQUIRE(myImage.getAlphaChannel() != nullptr);
        REQUIRE((*myImage.getAlphaChannel())->getResolution() == myImage.getResolution());
    }

    SECTION("should not overwrite alpha channel") {
        Image myImage(16, 9);

        myImage.addAlphaChannel();
        (*myImage.getAlphaChannel())->setValue({2, 3}, Color::createWhite());
        myImage.addAlphaChannel();

        REQUIRE(myImage.channelNames() == std::vector<std::string_view>({"rgb", "alpha"}));
        REQUIRE((*myImage.getAlphaChannel())->getValue({2, 3}) == Color::createWhite());
    }
}

TEST_CASE("Image/addDepthChannel", "[Image]") {
    SECTION("should add depth channel") {
        Image myImage(16, 9);

        myImage.addDepthChannel();

        REQUIRE(myImage.channelNames() == std::vector<std::string_view>({"rgb", "depth"}));
        REQUIRE(myImage.hasDepthChannel());
        REQUIRE(myImage.getDepthChannel() != nullptr);
        REQUIRE((*myImage.getDepthChannel())->getResolution() == myImage.getResolution());
    }

    SECTION("should not overwrite depth channel") {
        Image myImage(16, 9);

        myImage.addDepthChannel();
        (*myImage.getDepthChannel())->setValue({2, 3}, Color::createWhite());
        myImage.addDepthChannel();

        REQUIRE(myImage.channelNames() == std::vector<std::string_view>({"rgb", "depth"}));
        REQUIRE((*myImage.getDepthChannel())->getValue({2, 3}) == Color::createWhite());
    }
}

TEST_CASE("Image/addChannel", "[Image]") {
    SECTION("order should be maintained") {
        Image myImage(16, 9);

        myImage.addAlphaChannel();
        myImage.addDepthChannel();
        myImage.addChannel("custom", PixelBuffer::createRgbFloat({16, 9}));

        REQUIRE(myImage.channelNames() == std::vector<std::string_view>({"rgb", "alpha", "depth", "custom"}));
    }

    SECTION("should add a custom channel") {
        Image myImage(16, 9);

        myImage.addChannel("custom", PixelBuffer::createRgbFloat({16, 9}));

        REQUIRE(myImage.channelNames() == std::vector<std::string_view>({"rgb", "custom"}));
        REQUIRE(myImage.getChannel("custom") != nullptr);
    }
}

TEST_CASE("Image/getChannel", "[Image]") {
    SECTION("should return rgb channel") {
        Image myImage(16, 9);

        REQUIRE(myImage.getChannel("rgb"));
    }

    SECTION("should return empty optional for not existing channel") {
        Image myImage(16, 9);

        REQUIRE_FALSE(myImage.getChannel("alpha"));
    }

    SECTION("should return custom channel") {
        Image myImage(16, 9);
        myImage.addAlphaChannel();

        REQUIRE(myImage.getChannel("alpha"));
    }
}

TEST_CASE("Image/hasChannel", "[Image]") {
    SECTION("should return true for rgb channel") {
        Image myImage(16, 9);

        REQUIRE(myImage.hasChannel("rgb"));
    }

    SECTION("should return false for not existing channel") {
        Image myImage(16, 9);

        REQUIRE_FALSE(myImage.hasChannel("alpha"));
    }

    SECTION("should return true for custom channel") {
        Image myImage(16, 9);
        myImage.addAlphaChannel();

        REQUIRE(myImage.hasChannel("alpha"));
    }
}

TEST_CASE("Image/getChannels", "[Image]") {
    SECTION("should return only rgb") {
        Image myImage(16, 9);

        auto channels = myImage.getChannels();

        REQUIRE(channels.size() == 1);
        REQUIRE(channels[0].channelName == "rgb");
        REQUIRE(channels[0].channelBuffer == myImage.rgb);
    }

    SECTION("should return channels") {
        Image myImage(16, 9);
        myImage.addAlphaChannel();

        auto channels = myImage.getChannels();

        REQUIRE(channels.size() == 2);
        REQUIRE(channels[0].channelName == "rgb");
        REQUIRE(channels[1].channelName == "alpha");
    }
}

TEST_CASE("Image/replaceChannel", "[Image]") {
    SECTION("should replace rgb channel") {
        Image myImage(16, 9);
        myImage.setValue(2, 3, Color::createWhite());

        myImage.replaceChannel("rgb", PixelBuffer::createRgbUInt8(myImage.getResolution()));
        REQUIRE(myImage.getValue(2, 3) == Color::createBlack());
    }

    SECTION("should replace additional channel") {
        Image myImage(16, 9);
        myImage.addAlphaChannel();
        (*myImage.getAlphaChannel())->setValue({2, 3}, Color::createWhite());

        myImage.replaceChannel("alpha", PixelBuffer::createGreyFloat(myImage.getResolution()));

        REQUIRE(myImage.channelNames() == std::vector<std::string_view>({"rgb", "alpha"}));
        REQUIRE((*myImage.getAlphaChannel())->getValue({2, 3}) == Color::createBlack());
    }
}

TEST_CASE("Image/getResolution", "[Image]") {
    Image image(10, 20);

    REQUIRE(image.getResolution() == Resolution(10, 20));
}

TEST_CASE("Image/getImageSpec", "[Image]") {

    SECTION("should return correct spec for rgb-only image") {
        Image image(10, 20);

        REQUIRE(image.getImageSpec() == ImageSpec({10, 20}, {{"rgb", PixelFormat::FLOAT, 3}}));
    }

    SECTION("should return correct spec for rgb-only image") {
        Image image(10, 20);
        image.addAlphaChannel();
        image.addDepthChannel();

        REQUIRE(image.getImageSpec() == ImageSpec({10, 20}, {{"rgb", PixelFormat::FLOAT, 3},
                                                             {"alpha", PixelFormat::FLOAT, 1},
                                                             {"depth", PixelFormat::FLOAT, 1}}));
    }
}

TEST_CASE("Image/addChannelsFromSpec", "[Image]") {

    SECTION("should throw if resolutions do not match") {
        Image image(10, 20);
        ImageSpec imageSpec({1, 1}, {{"rgb", PixelFormat::FLOAT, 3}});

        REQUIRE_THROWS_AS(image.addChannelsFromSpec(imageSpec), std::runtime_error);
    }

    SECTION("should add channels from spec") {
        Image image(10, 20);
        ImageSpec imageSpec(
            {10, 20},
            {{"rgb", PixelFormat::FLOAT, 3}, {"alpha", PixelFormat::FLOAT, 1}, {"depth", PixelFormat::FLOAT, 1}});

        image.addChannelsFromSpec(imageSpec);

        REQUIRE(image.getImageSpec() == ImageSpec({10, 20}, {{"rgb", PixelFormat::FLOAT, 3},
                                                             {"alpha", PixelFormat::FLOAT, 1},
                                                             {"depth", PixelFormat::FLOAT, 1}}));
    }
}

}
