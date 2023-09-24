#include "CliParser.h"
#include "CLI/CLI.hpp"
#include "CraygInfo.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <sstream>

namespace crayg {

template <typename T> CLI::CheckedTransformer createEnumTransformer() {
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

std::vector<SceneReaderVariantSelection> parseVariantSelections(const std::vector<std::string> &variantSelections) {
    std::vector<SceneReaderVariantSelection> parsedVariantSelections;

    for (auto &variantSelection : variantSelections) {
        std::vector<std::string> splitByColumnResult;
        boost::algorithm::split(splitByColumnResult, variantSelection, boost::is_any_of(":"));
        if (splitByColumnResult.size() != 2) {
            throw std::runtime_error(fmt::format("Invalid variant selection string: '{}'", variantSelection));
        }

        std::vector<std::string> splitByEqualSignResult;
        boost::algorithm::split(splitByEqualSignResult, splitByColumnResult[1], boost::is_any_of("="));
        if (splitByEqualSignResult.size() != 2) {
            throw std::runtime_error(fmt::format("Invalid variant selection string: '{}'", variantSelection));
        }

        const std::string primPath = splitByColumnResult[0];
        const std::string variantSetName = splitByEqualSignResult[0];
        const std::string selectedVariant = splitByEqualSignResult[1];
        parsedVariantSelections.push_back({primPath, variantSetName, selectedVariant});
    }

    return parsedVariantSelections;
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

    std::vector<std::string> variantSelections;
    app.add_option("--variantSelection", variantSelections,
                   "Variant selections to apply to USD Stage. Format: /prim/path:variant_set=variant_name");

    CliRenderSettingsOverride renderSettingsOverride;

    std::string resolution;
    app.add_option("--resolution", resolution, "Override resolution to render, format: 1280x720");

    app.add_option("--maxSamples", renderSettingsOverride.maxSamples, "Override max samples");

    app.add_option("--integrator", renderSettingsOverride.integratorType, "Override integrator")
        ->transform(createEnumTransformer<IntegratorType>());

    app.add_option("--intersector", renderSettingsOverride.intersectorType, "Override intersector")
        ->transform(createEnumTransformer<IntersectorType>());

    app.add_option("--bucketSequence", renderSettingsOverride.bucketSequenceType, "Override bucket sequence")
        ->transform(createEnumTransformer<BucketSequenceType>());

    app.add_option("--bucketSamplerType", renderSettingsOverride.bucketSamplerType, "Use adaptive sampling")
        ->transform(createEnumTransformer<BucketSamplerType>());

    app.add_option("--adaptiveMaxError", renderSettingsOverride.adaptiveMaxError, "Override adaptive max error");

    app.add_option("--samplesPerAdaptivePass", renderSettingsOverride.samplesPerAdaptivePass,
                   "Override samples per adaptive pass");

    std::optional<bool> useSpectralLensing;
    app.add_flag("--useSpectralLensing", renderSettingsOverride.useSpectralLensing,
                 "Override if spectral lens simulation should be used");

    try {
        app.parse(argc, argv);

        if (!resolution.empty()) {
            renderSettingsOverride.resolution = Resolution::parse(resolution);
        }

        std::vector<SceneReaderVariantSelection> parsedVariantSelections = parseVariantSelections(variantSelections);

        return CliParseResult(CliArgs(sceneFileName, imageOutputPath,
                                      !cameraName.empty() ? std::make_optional(cameraName) : std::nullopt,
                                      renderSettingsOverride, parsedVariantSelections),
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
                 CliRenderSettingsOverride cliRenderSettingsOverride,
                 const std::vector<SceneReaderVariantSelection> &variantSelections)
    : scenePath(scenePath), imageOutputPath(imageOutputPath), cameraName(cameraName),
      cliRenderSettingsOverride(cliRenderSettingsOverride), variantSelections(variantSelections) {
}
}