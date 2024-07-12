#include "CLI/CLI.hpp"
#include "CraygInfo.h"
#include "Logger.h"
#include <filesystem>

#include "scene/camera/realistic/ExitPupilCalculator.h"
#include "scene/camera/realistic/lensio/LensFileReaderFactory.h"
#include "scene/camera/realistic/lensio/LensFileWriterFactory.h"
#include "utils/CraygMain.h"
#include "utils/DtoUtils.h"
#include "utils/EnumUtils.h"
#include <nlohmann/json.hpp>

namespace crayg {

CRAYG_DTO_3(LensFileConversionOptions, std::string, inputFile, std::string, outputFile, std::string, format);

struct LensFileScaleOptions {
    std::string inputFile;
    std::string outputFile;
    std::vector<float> focalLengths;
};

void convertLensFile(const LensFileConversionOptions &options) {
    auto lensFileReader = LensFileReaderFactory::createLensFileReader(options.inputFile);
    auto cameraLens = lensFileReader->readFile(options.inputFile);

    if (options.outputFile.empty()) {
        auto format = EnumUtils::parseOrThrow<LensFileFormat>(options.format);
        auto writer = LensFileWriterFactory::createLensFileWriter(format);
        auto content = writer->writeFileContent(cameraLens);
        std::cout << content << std::endl;
        return;
    }

    auto writer = LensFileWriterFactory::createLensFileWriter(options.outputFile);
    writer->writeFile(options.outputFile, cameraLens);
}

void scaleLensFile(const LensFileScaleOptions &options) {
    auto lensFileReader = LensFileReaderFactory::createLensFileReader(options.inputFile);
    auto cameraLens = lensFileReader->readFile(options.inputFile);
    Logger::info("Original focal length: {}mm", cameraLens.metadata.focalLength * 10);
    for (auto targetFocalLength : options.focalLengths) {
        const float ratio = targetFocalLength / (cameraLens.metadata.focalLength * 10);
        auto scaled = cameraLens.surfaces;
        for (auto &surface : scaled) {
            surface.apertureRadius *= ratio;
            surface.curvatureRadius *= ratio;
            surface.thickness *= ratio;
        }
        auto scaledLens = CameraLens(cameraLens.metadata, scaled);
        auto path = std::filesystem::path(options.outputFile);
        const std::string targetPath =
            (std::filesystem::absolute(path).parent_path() /
             fmt::format("{}-{}mm{}", path.stem().string(), targetFocalLength, path.extension().string()))
                .string();
        auto writer = LensFileWriterFactory::createLensFileWriter(targetPath);
        writer->writeFile(targetPath, scaledLens);
        Logger::info("Wrote {}", targetPath);
    }
}

float mse(const std::vector<float> &data) {
    float result = 0;
    for (auto f : data) {
        result += f * f;
    }
    return result / data.size();
}

void calculateLensMaterialError(const std::string &inputFile) {
    auto lensFileReader = LensFileReaderFactory::createLensFileReader(inputFile);
    auto cameraLens = lensFileReader->readFile(inputFile);
    std::vector<float> iorErrors;
    std::vector<float> abbeErrors;

    for (auto &lens : cameraLens.surfaces) {
        if (lens.ior == 1 || lens.ior == 0) {
            continue;
        }
        iorErrors.push_back(std::abs(lens.ior - lens.material.ior));
        abbeErrors.push_back(std::abs(lens.abbeNumber - lens.material.abbeNo));
    }

    const float minIorError = *std::min_element(iorErrors.begin(), iorErrors.end());
    const float maxIorError = *std::max_element(iorErrors.begin(), iorErrors.end());
    const float iorMse = mse(iorErrors);

    const float minAbbeNoError = *std::min_element(abbeErrors.begin(), abbeErrors.end());
    const float maxAbbeNoError = *std::max_element(abbeErrors.begin(), abbeErrors.end());
    const float abbeNoMse = mse(iorErrors);

    fmt::print("IOR errors:\n");
    for (auto f : iorErrors) {
        fmt::print("{}\n", f);
    }
    fmt::print("Min IOR error: {}\n", minIorError);
    fmt::print("Max IOR error: {}\n", maxIorError);
    fmt::print("IOR error MSE: {}\n", iorMse);

    fmt::print("Abbe No errors:\n");
    for (auto f : abbeErrors) {
        fmt::print("{}\n", f);
    }
    fmt::print("Min Abbe no error: {}\n", minAbbeNoError);
    fmt::print("Max Abbe no error: {}\n", maxAbbeNoError);
    fmt::print("Abbe no error MSE: {}\n", abbeNoMse);
}

void calculateExitPupilBounds(const std::string &inputFile) {
    auto lensFileReader = LensFileReaderFactory::createLensFileReader(inputFile);
    auto cameraLens = lensFileReader->readFile(inputFile);
    NullTaskReporter taskReporter;
    ExitPupilCalculator exitPupilCalculator(cameraLens, Vector2f(3.670f, 2.554f).length(),
                                            ExitPupilCalculator::CalculationSettings(), taskReporter);

    auto exitPupils = nlohmann::json::array();
    const float start = 60;
    const float end = 1000;
    for (float d = start; d < end; d += 10) {
        Logger::info("Calculating exit pupil for {}cm", d);
        cameraLens.focusLens(d);
        auto exitPupil = exitPupilCalculator.calculate();
        auto exitPupilJson = nlohmann::json::object();
        exitPupilJson["focusDistance"] = d;
        exitPupilJson["pupilBounds"] = nlohmann::json::array();
        for (auto &bound : exitPupil.pupilBounds) {
            auto boundJson = {bound.min.x, bound.min.y, bound.max.x, bound.max.y};
            exitPupilJson["pupilBounds"].push_back(boundJson);
        }
        exitPupils.push_back(exitPupilJson);
    }

    std::ofstream o("C:\\workspace\\crayg\\pupils\\pupils.json");
    o << exitPupils.dump(4);
    o.close();
}

int craygMain(int argc, char *argv[]) {
    CLI::App app{
        fmt::format("Crayg lensfile utils {}, commit {}", crayg::CraygInfo::VERSION, crayg::CraygInfo::COMMIT_HASH),
        "lensfileutils"};
    app.require_subcommand(1);

    auto convertCommand = app.add_subcommand("convert", "converts a lens file from one format to another");

    std::string lensFileInput;
    convertCommand->add_option("-i,--input", lensFileInput, "Lens file input")->required();

    std::string lensFileOutput;
    convertCommand->add_option("-o,--output", lensFileOutput, "Lens file output. Outputs to stdout if not specified")
        ->required(false);

    std::string format = "json";
    convertCommand->add_option("-f,--format", format, "Lens file format, available options: json (default), txt")
        ->required(false);

    auto scaleCommand = app.add_subcommand("scale", "outputs different scaling for a given lens file");

    scaleCommand->add_option("-i,--input", lensFileInput, "Lens file input")->required();

    std::vector<float> focalLengths_mm;
    scaleCommand->add_option("-f,--focal-lengths", focalLengths_mm, "focal lengths (mm) to scale to")->required();

    scaleCommand->add_option("-o,--output", lensFileOutput, "Lens file output. Outputs to stdout if not specified")
        ->required(false);

    auto convertGlasMaterialErrorCommand =
        app.add_subcommand("material-error", "outputs the errors of the chosen lens materials");

    convertGlasMaterialErrorCommand->add_option("-i,--input", lensFileInput, "Lens file input")->required();

    auto calculateExitPupilBoundsCommand = app.add_subcommand("exit-pupil-bounds", "outputs the exit pupils");

    calculateExitPupilBoundsCommand->add_option("-i,--input", lensFileInput, "Lens file input")->required();

    try {
        app.parse(argc, argv);

    } catch (const CLI::Error &e) {
        exit(app.exit(e));
    }

    if (convertCommand->parsed()) {
        convertLensFile({lensFileInput, lensFileOutput, format});
    } else if (scaleCommand->parsed()) {
        scaleLensFile({lensFileInput, lensFileOutput, focalLengths_mm});
    } else if (convertGlasMaterialErrorCommand->parsed()) {
        calculateLensMaterialError(lensFileInput);
    } else if (calculateExitPupilBoundsCommand->parsed()) {
        calculateExitPupilBounds(lensFileInput);
    }
    return 0;
}

}

int main(int argc, char *argv[]) {
    CRAYG_MAIN_IMPL;
}