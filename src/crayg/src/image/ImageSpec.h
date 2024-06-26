#pragma once

#include "PixelFormat.h"
#include "basics/Resolution.h"
#include "utils/DtoUtils.h"
#include <vector>

namespace crayg {

CRAYG_DTO_3(ChannelSpec, std::string, name, PixelFormat, pixelFormat, int, colorChannelCount);

CRAYG_DTO_2(ImageSpec, Resolution, resolution, std::vector<ChannelSpec>, channels);

class ImageSpecBuilder {
  public:
    ImageSpecBuilder(const Resolution &resolution) {
        imageSpec = ImageSpec(resolution, {{"rgb", PixelFormat::FLOAT, 3}});
    }

    ImageSpecBuilder &addAlphaChannel() {
        createGreyFloatChannel("alpha");
        return *this;
    }

    ImageSpecBuilder &addDepthChannel() {
        createGreyFloatChannel("depth");
        return *this;
    }

    ImageSpecBuilder &createRgbFloatChannel(const std::string &name) {
        imageSpec.channels.emplace_back(name, PixelFormat::FLOAT, 3);
        return *this;
    }

    ImageSpecBuilder &createGreyFloatChannel(const std::string &name) {
        imageSpec.channels.emplace_back(name, PixelFormat::FLOAT, 1);
        return *this;
    }

    ImageSpecBuilder &createRgbUInt8Channel(const std::string &name) {
        imageSpec.channels.emplace_back(name, PixelFormat::UINT8, 3);
        return *this;
    }

    ImageSpecBuilder &createGreyUInt8Channel(const std::string &name) {
        imageSpec.channels.emplace_back(name, PixelFormat::UINT8, 1);
        return *this;
    }

    ImageSpecBuilder &createVector3fChannel(const std::string &name) {
        imageSpec.channels.emplace_back(name, PixelFormat::FLOAT, 3);
        return *this;
    }

    ImageSpec finish() {
        return imageSpec;
    }

  private:
    ImageSpec imageSpec;
};

} // crayg
