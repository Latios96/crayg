#include "FilmSpec.h"

namespace crayg {

FilmBufferSpec::FilmBufferSpec(const std::string &name, FilmBufferType bufferType, PixelFormat pixelFormat,
                               int channelCount)
    : name(name), bufferType(bufferType), pixelFormat(pixelFormat), channelCount(channelCount) {
}

bool FilmBufferSpec::operator==(const FilmBufferSpec &rhs) const {
    return name == rhs.name && bufferType == rhs.bufferType && pixelFormat == rhs.pixelFormat &&
           channelCount == rhs.channelCount;
}

bool FilmBufferSpec::operator!=(const FilmBufferSpec &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const FilmBufferSpec &spec) {
    os << ToStringHelper("FilmBufferSpec")
              .addMember("name", spec.name)
              .addMember("bufferType", spec.bufferType)
              .addMember("pixelFormat", spec.pixelFormat)
              .addMember("channelCount", spec.channelCount)
              .finish();
    return os;
}

FilmSpecBuilder::FilmSpecBuilder(const Resolution &resolution) {
    filmSpec = FilmSpec(resolution, {{"color", FilmBufferType::ACCUMULATION, PixelFormat::FLOAT32, 3}}, std::nullopt);
}

FilmSpecBuilder &FilmSpecBuilder::addChannel(const FilmBufferSpec &spec) {
    filmSpec.channels.emplace_back(spec);
    return *this;
}

FilmSpecBuilder &FilmSpecBuilder::addRenderRegion(const RegionToRender &regionToRender) {
    filmSpec.regionToRender = regionToRender.toPixelRegion(filmSpec.resolution);
    return *this;
}

FilmSpec FilmSpecBuilder::finish() {
    return filmSpec;
}
}