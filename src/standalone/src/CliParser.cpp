#include "CliParser.h"
#include "CLI/CLI.hpp"
#include "CraygInfo.h"
#include "utils/Exceptions.h"
#include "utils/FromStringUtils.h"
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
            CRAYG_LOG_AND_THROW(
                std::runtime_error(fmt::format("Invalid variant selection string: '{}'", variantSelection)));
        }

        std::vector<std::string> splitByEqualSignResult;
        boost::algorithm::split(splitByEqualSignResult, splitByColumnResult[1], boost::is_any_of("="));
        if (splitByEqualSignResult.size() != 2) {
            CRAYG_LOG_AND_THROW(
                std::runtime_error(fmt::format("Invalid variant selection string: '{}'", variantSelection)));
        }

        const std::string primPath = splitByColumnResult[0];
        const std::string variantSetName = splitByEqualSignResult[0];
        const std::string selectedVariant = splitByEqualSignResult[1];
        parsedVariantSelections.push_back({primPath, variantSetName, selectedVariant});
    }

    return parsedVariantSelections;
}

template <typename T> T parseIntegratorSettingsValue(const std::string &str);

template <> int parseIntegratorSettingsValue(const std::string &str) {
    return FromStringUtils::parseIntOrThrow(str);
}

template <> float parseIntegratorSettingsValue(const std::string &str) {
    return stof(str);
}

template <> std::string parseIntegratorSettingsValue(const std::string &str) {
    return str;
}

template <typename T>
void parseIntegratorSettings(std::vector<IntegratorSettingsOverride> &integratorSettingsOverrides,
                             const std::vector<std::string> &overrideStrings) {

    for (auto &overrideString : overrideStrings) {
        std::vector<std::string> splittedOverrideString;
        boost::algorithm::split(splittedOverrideString, overrideString, boost::algorithm::is_any_of("="));
        const bool overrideStringHasTwoElements = splittedOverrideString.size() != 2;
        const bool elementsAreNotEmpty =
            overrideStringHasTwoElements && !(splittedOverrideString[0].empty() || splittedOverrideString[1].empty());
        if (overrideStringHasTwoElements && elementsAreNotEmpty) {
            CRAYG_LOG_AND_THROW(
                std::runtime_error(fmt::format("Invalid integrator settings override: '{}'", overrideString)));
        }

        T value = parseIntegratorSettingsValue<T>(splittedOverrideString[1]);
        integratorSettingsOverrides.emplace_back(splittedOverrideString[0], value);
    }
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

    std::vector<std::string> integratorSettingsIntOverrides;
    app.add_option("--integrator-setting-int", integratorSettingsIntOverrides,
                   "Override integrator settings. Format: INTEGRATOR_NAME:settingsName=value");
    std::vector<std::string> integratorSettingsFloatOverrides;
    app.add_option("--integrator-setting-float", integratorSettingsFloatOverrides,
                   "Override integrator settings. Format: INTEGRATOR_NAME:settingsName=value");
    std::vector<std::string> integratorSettingsStringOverrides;
    app.add_option("--integrator-setting-string", integratorSettingsStringOverrides,
                   "Override integrator settings. Format: INTEGRATOR_NAME:settingsName=value");

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

    app.add_flag("--useSpectralLensing", renderSettingsOverride.useSpectralLensing,
                 "Override if spectral lens simulation should be used");

    std::string regionToRender;
    app.add_flag("--regionToRender", regionToRender,
                 "Render only a specified region, provide in [(min_x,mix_y),(max_x,max_y)]");

    try {
        app.parse(argc, argv);

        if (!resolution.empty()) {
            renderSettingsOverride.resolution = Resolution::parse(resolution);
        }

        std::vector<SceneReaderVariantSelection> parsedVariantSelections = parseVariantSelections(variantSelections);

        parseIntegratorSettings<int>(renderSettingsOverride.integratorSettingsOverrides,
                                     integratorSettingsIntOverrides);
        parseIntegratorSettings<float>(renderSettingsOverride.integratorSettingsOverrides,
                                       integratorSettingsFloatOverrides);
        parseIntegratorSettings<std::string>(renderSettingsOverride.integratorSettingsOverrides,
                                             integratorSettingsStringOverrides);

        if (!regionToRender.empty()) {
            renderSettingsOverride.regionToRender = RegionToRender::fromString(regionToRender);
        }

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