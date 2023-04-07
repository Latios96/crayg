#include "CLI/CLI.hpp"
#include "CraygInfo.h"
#include "Logger.h"

#include "scene/camera/lensio/LensFileReaderFactory.h"
#include "scene/camera/lensio/LensFileWriterFactory.h"
#include "utils/DtoUtils.h"
#include "utils/EnumUtils.h"

namespace crayg {

CRAYG_DTO_3(LensFileConversionOptions, std::string, inputFile, std::string, outputFile, std::string, format);

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

}

int main(int argc, char **argv) {
    crayg::Logger::initialize();
    try {
        CLI::App app{
            fmt::format("Crayg lensfile utils {}, commit {}", crayg::CraygInfo::VERSION, crayg::CraygInfo::COMMIT_HASH),
            "lensfileutils"};
        app.require_subcommand(1);

        auto convertCommand = app.add_subcommand("convert", "converts a lens file from one format to another");

        std::string lensFileInput;
        convertCommand->add_option("-i,--input", lensFileInput, "Lens file input")->required();

        std::string lensFileOutput;
        convertCommand
            ->add_option("-o,--output", lensFileOutput, "Lens file output. Outputs to stdout if not specified")
            ->required(false);

        std::string format = "json";
        convertCommand->add_option("-f,--format", format, "Lens file format, available options: json (default), txt")
            ->required(false);

        app.parse(argc, argv);

        if (convertCommand->parsed()) {
            crayg::convertLensFile({lensFileInput, lensFileOutput, format});
        }

    } catch (std::exception &e) {
        crayg::Logger::error("Caught exception: {}", e.what());
        return -1;
    }
};