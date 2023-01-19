#include "ImageMetadataCollector.h"
#include "CraygInfo.h"
#include <cpuinfo.h>
#include <fmt/chrono.h>

namespace crayg {

ImageMetadataCollector::ImageMetadataCollector(){}

ImageMetadataCollector::ImageMetadataCollector(const std::optional<std::chrono::seconds> &renderTime,
                                               const std::optional<RenderSettings> &renderSettings) : renderTime(
    renderTime), renderSettings(renderSettings) {}

ImageMetadata ImageMetadataCollector::collectMetadata() {
    ImageMetadata imageMetadata;

    collectCraygVersion(imageMetadata);
    collectCpuName(imageMetadata);
    collectRenderTimeIfPresent(imageMetadata);
    collectRenderSettingsIfPresent(imageMetadata);

    return imageMetadata;
}

void ImageMetadataCollector::collectCraygVersion(ImageMetadata &imageMetadata) const {
    imageMetadata.write(ImageMetadataTokens::CRAYG_VERSION,
                        fmt::format("{}-{}", CraygInfo::VERSION, CraygInfo::COMMIT_HASH));
}

void ImageMetadataCollector::collectCpuName(ImageMetadata &imageMetadata) const {
    cpuinfo_initialize();
    imageMetadata.write(ImageMetadataTokens::CPU, cpuinfo_get_package(0)->name);
}

void ImageMetadataCollector::collectRenderTimeIfPresent(ImageMetadata &imageMetadata) {
    if (renderTime) {
        imageMetadata.write(ImageMetadataTokens::RENDER_TIME, fmt::format("{:%T}", renderTime.value()));
        imageMetadata.write(ImageMetadataTokens::RENDER_TIME_SECONDS, renderTime.value());
    }
}

void ImageMetadataCollector::collectRenderSettingsIfPresent(ImageMetadata &imageMetadata) {
    if (renderSettings) {
        imageMetadata.write(ImageMetadataTokens::RENDER_SETTINGS_INTEGRATOR,
                            std::string(magic_enum::enum_name(renderSettings.value().integratorType)));
        imageMetadata.write(ImageMetadataTokens::RENDER_SETTINGS_INTERSECTOR,
                            std::string(magic_enum::enum_name(renderSettings.value().intersectorType)));
        imageMetadata.write(ImageMetadataTokens::RENDER_SETTINGS_MAX_SAMPLES, renderSettings.value().maxSamples);
        collectIntegratorSettings(imageMetadata);
    }
}

void ImageMetadataCollector::collectIntegratorSettings(ImageMetadata &imageMetadata) {
    for (const auto &entry: renderSettings.value().integratorSettings.settings) {
        switch (entry.second.index()) {
            case 0:
                imageMetadata.write("crayg/renderSettings/integratorSettings/" + entry.first,
                                    std::get<std::string>(entry.second));
                break;
            case 1:
                imageMetadata.write("crayg/renderSettings/integratorSettings/" + entry.first,
                                    std::get<int>(entry.second));
                break;
            case 2:
                imageMetadata.write("crayg/renderSettings/integratorSettings/" + entry.first,
                                    std::get<float>(entry.second));
                break;
        }
    }
}

} // crayg