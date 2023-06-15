#include "CLI/CLI.hpp"
#include "CraygInfo.h"
#include "Logger.h"
#include <boost/filesystem.hpp>

#include "scene/camera/lensio/LensFileReaderFactory.h"
#include "scene/camera/lensio/LensFileWriterFactory.h"
#include "utils/CraygMain.h"
#include "utils/DtoUtils.h"
#include "utils/EnumUtils.h"

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
    Logger::info("Original focal length: {}mm", cameraLens.focalLength * 10);
    for (auto targetFocalLength : options.focalLengths) {
        const float ratio = targetFocalLength / (cameraLens.focalLength * 10);
        auto scaled = cameraLens.elements;
        for (auto &element : scaled) {
            element.apertureRadius *= ratio;
            element.curvatureRadius *= ratio;
            element.thickness *= ratio;
        }
        auto scaledLens = CameraLens(cameraLens.name, scaled);
        auto path = boost::filesystem::path(options.outputFile);
        const std::string targetPath =
            (boost::filesystem::absolute(path).parent_path() /
             fmt::format("{}-{}mm{}", path.stem().string(), targetFocalLength, path.extension().string()))
                .string();
        auto writer = LensFileWriterFactory::createLensFileWriter(targetPath);
        writer->writeFile(targetPath, scaledLens);
        Logger::info("Wrote {}", targetPath);
    }
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

    try {
        app.parse(argc, argv);

    } catch (const CLI::Error &e) {
        exit(app.exit(e));
    }

    if (convertCommand->parsed()) {
        convertLensFile({lensFileInput, lensFileOutput, format});
    } else if (scaleCommand->parsed()) {
        scaleLensFile({lensFileInput, lensFileOutput, focalLengths_mm});
    }
    return 0;
}

}

int main(int argc, char *argv[]) {
    CRAYG_MAIN_IMPL;
}