#include "FilmSpec.h"

namespace crayg {

FilmBufferSpec::FilmBufferSpec(const std::string &name, FilmBufferType bufferType, FilmPixelDepth pixelDepth,
                               int channelCount)
    : name(name), bufferType(bufferType), pixelDepth(pixelDepth), channelCount(channelCount) {
}

bool FilmBufferSpec::operator==(const FilmBufferSpec &rhs) const {
    return name == rhs.name && bufferType == rhs.bufferType && pixelDepth == rhs.pixelDepth &&
           channelCount == rhs.channelCount;
}

bool FilmBufferSpec::operator!=(const FilmBufferSpec &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const FilmBufferSpec &spec) {
    os << ToStringHelper("FilmBufferSpec")
              .addMember("name", spec.name)
              .addMember("bufferType", spec.bufferType)
              .addMember("pixelDepth", spec.pixelDepth)
              .addMember("channelCount", spec.channelCount)
              .finish();
    return os;
}

FilmSpecBuilder::FilmSpecBuilder(const Resolution &resolution) {
    filmSpec = FilmSpec(resolution, {{"rgb", FilmBufferType::ACCUMULATION, FilmPixelDepth::FLOAT32, 3}}, std::nullopt);
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