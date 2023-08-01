#include "CliParser.h"
#include "CLI/CLI.hpp"
#include "CraygInfo.h"
#include <boost/algorithm/string/join.hpp>
#include <sstream>

namespace crayg {

template <typename T> CLI::CheckedTransformer createTransformer() {
    constexpr auto entries = magic_enum::enum_entries<T>();
    std::map<std::string, T> map;
    for (auto &entry : entries) {
        map[std::string(entry.second)] = entry.first;
    }
    return CLI::CheckedTransformer(map, CLI::ignore_case);
}

CliParser::CliParser(const std::string &executableName, int argc, char **argv)
    : argc(argc), argv(argv), executableName(executableName) {
}

CliParseResult CliParser::parse() {
    CLI::App app{
        fmt::format("Crayg Renderer version {}, commit {}", crayg::CraygInfo::VERSION, crayg::CraygInfo::COMMIT_HASH),
        executableName};

    std::string sceneFileName;
    app.add_option("-s,--scene", sceneFileName, "Scene file to render")->required();

    std::string imageOutputPath;
    app.add_option("-o,--output", imageOutputPath, "Path where rendered image is saved")->required();

    std::string cameraName;
    app.add_option("--camera", cameraName,
                   "Name of the camera to render. Defaulting to the first camera found in the scene");

    std::string resolution;
    app.add_option("--resolution", resolution, "Override resolution to render, format: 1280x720");

    int maxSamples = 0;
    app.add_option("--maxSamples", maxSamples, "Override max samples");

    std::optional<IntegratorType> integratorType;
    app.add_option("--integrator", integratorType, "Override integrator")
        ->transform(createTransformer<IntegratorType>());

    std::optional<IntersectorType> intersectorType;
    app.add_option("--intersector", intersectorType, "Override intersector")
        ->transform(createTransformer<IntersectorType>());

    std::optional<BucketSequenceType> bucketSequenceType;
    app.add_option("--bucketSequence", bucketSequenceType, "Override bucket sequence")
        ->transform(createTransformer<BucketSequenceType>());

    std::optional<BucketSamplerType> bucketSamplerType;
    app.add_option("--bucketSamplerType", bucketSamplerType, "Use adaptive sampling")
        ->transform(createTransformer<BucketSamplerType>());

    std::optional<float> adaptiveMaxError;
    app.add_option("--adaptiveMaxError", adaptiveMaxError, "Override adaptive max error");

    std::optional<int> samplesPerAdaptivePass;
    app.add_option("--samplesPerAdaptivePass", samplesPerAdaptivePass, "Override samples per adaptive pass");

    std::optional<bool> useSpectralLensing;
    app.add_flag("--useSpectralLensing", useSpectralLensing, "Override if spectral lens simulation should be used");

    try {
        app.parse(argc, argv);

        CliRenderSettingsOverride renderSettingsOverride;
        if (!resolution.empty()) {
            renderSettingsOverride.resolution = Resolution::parse(resolution);
        }
        if (maxSamples) {
            renderSettingsOverride.maxSamples = maxSamples;
        }
        if (integratorType) {
            renderSettingsOverride.integratorType = integratorType.value();
        }
        if (intersectorType) {
            renderSettingsOverride.intersectorType = intersectorType.value();
        }
        if (bucketSequenceType) {
            renderSettingsOverride.bucketSequenceType = bucketSequenceType.value();
        }
        if (bucketSamplerType) {
            renderSettingsOverride.bucketSamplerType = bucketSamplerType.value();
        }
        if (adaptiveMaxError) {
            renderSettingsOverride.adaptiveMaxError = adaptiveMaxError.value();
        }
        if (samplesPerAdaptivePass) {
            renderSettingsOverride.samplesPerAdaptivePass = samplesPerAdaptivePass.value();
        }
        if (useSpectralLensing) {
            renderSettingsOverride.useSpectralLensing = useSpectralLensing.value();
        }

        return CliParseResult(CliArgs(sceneFileName, imageOutputPath,
                                      !cameraName.empty() ? std::make_optional(cameraName) : std::nullopt,
                                      renderSettingsOverride),
                              std::nullopt);
    } catch (const CLI::Error &e) {
        std::stringstream out;
        app.exit(e, out, out);
        return CliParseResult(std::nullopt, std::optional<std::string>(out.str()));
    } catch (const std::runtime_error &e) {
        const std::string &right = app.help("", CLI::AppFormatMode::All);
        return CliParseResult(std::nullopt, std::optional<std::string>(right));
    }
}

CliArgs::CliArgs(std::string scenePath, std::string imageOutputPath, std::optional<std::string> cameraName,
                 CliRenderSettingsOverride cliRenderSettingsOverride)
    : scenePath(scenePath), imageOutputPath(imageOutputPath), cameraName(cameraName),
      cliRenderSettingsOverride(cliRenderSettingsOverride) {
}
}