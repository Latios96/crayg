#pragma once
#include "image/Image.h"
#include "image/film/Film.h"
#include "image/imageiterators/pixels/ImageIterators.h"

namespace crayg {

const Bounds2d<int> RENDER_REGION_BOUNDS = Bounds2di({9, 9}, {127 - 9, 71 - 9});

struct ImageFixture {
    ImageFixture(bool addMetadata = true) : image(Image(128, 72)) {
        createRgbGradientImage(image.rgb, image.getResolution().toBounds());
        if (addMetadata) {
            addTestMetadata();
        }
    }

    ImageFixture(const Bounds2di &valueBounds, bool addMetadata = true, bool valuesOnlyInBounds = false)
        : image(Image(128, 72)) {
        if (valuesOnlyInBounds) {
            createRgbGradientImage(image.rgb, valueBounds);
        } else {
            createRgbGradientImage(image.rgb, image.getResolution().toBounds());
        }

        if (addMetadata) {
            addTestMetadata();
        }
    }

    void addCustomChannel(PixelFormat pixelFormat, int colorChannelCount) {
        auto buffer = std::make_unique<PixelBuffer>(128, 72, pixelFormat, colorChannelCount);
        image.addChannel("custom", std::move(buffer));
        createRgbGradientImage(*image.getChannel("custom"), image.getResolution().toBounds());
    }

    Image image;

  private:
    void createRgbGradientImage(PixelBuffer &pixelBuffer, const Bounds2di &valueBounds) {
        for (auto pixel : ImageIterators::lineByLine(pixelBuffer)) {
            if (!valueBounds.contains(pixel)) {
                continue;
            }
            const float relativeX = static_cast<float>(pixel.x) / pixelBuffer.getWidth();
            const float relativeY = static_cast<float>(pixel.y) / pixelBuffer.getHeight();
            if (relativeY <= 0.33) {
                pixelBuffer.setValue(pixel, Color(relativeX, 0, 0));
            } else if (relativeY <= 0.66) {
                pixelBuffer.setValue(pixel, Color(0, relativeX, 0));
            } else {
                pixelBuffer.setValue(pixel, Color(0, 0, relativeX));
            }
        }
    }

    void addTestMetadata() {
        image.metadata.write("test/int", 42);
        image.metadata.write("test/float", 42.42f);
        image.metadata.write("test/string", "teststring");
        image.metadata.write("test/seconds", std::chrono::seconds(42));
    }
};

struct FilmFixture {
    FilmFixture(bool addMetadata = true) : film(Film(128, 72)) {
        createRgbGradientImage("color", film.getResolution().toBounds());
        if (addMetadata) {
            addTestMetadata();
        }
    }

    FilmFixture(const Bounds2di &valueBounds, bool addMetadata = true, bool valuesOnlyInBounds = false)
        : film(Film(FilmSpecBuilder({128, 72}).addRenderRegion(RegionToRender(RENDER_REGION_BOUNDS)).finish())) {
        if (valuesOnlyInBounds) {
            createRgbGradientImage("color", valueBounds);
        } else {
            createRgbGradientImage("color", film.getResolution().toBounds());
        }

        if (addMetadata) {
            addTestMetadata();
        }
    }

    void addCustomChannel(PixelFormat pixelFormat, int channelCount) {
        const FilmBufferVariantPtr &ptr =
            FilmBufferFactory::createFilmBuffer({128, 72}, FilmBufferType::VALUE, pixelFormat, channelCount);
        film.addChannel("custom", ptr);
        createRgbGradientImage("custom", film.getResolution().toBounds());
    }

    Film film;

  private:
    void createRgbGradientImage(const std::string &channelName, const Bounds2di &valueBounds) {
        const Resolution resolution = film.getResolution();
        for (auto pixel : ImageIterators::lineByLine(resolution)) {
            if (!valueBounds.contains(pixel)) {
                continue;
            }
            const float relativeX = static_cast<float>(pixel.x) / resolution.getWidth();
            const float relativeY = static_cast<float>(pixel.y) / resolution.getHeight();

            if (relativeY <= 0.33) {
                film.addSample(channelName, pixel, Color(relativeX, 0, 0));
            } else if (relativeY <= 0.66) {
                film.addSample(channelName, pixel, Color(0, relativeX, 0));
            } else {
                film.addSample(channelName, pixel, Color(0, 0, relativeX));
            }
        }
        film.updateAverages();
    }

    void addTestMetadata() {
        film.metadata.write("test/int", 42);
        film.metadata.write("test/float", 42.42f);
        film.metadata.write("test/string", "teststring");
        film.metadata.write("test/seconds", std::chrono::seconds(42));
    }
};

}
