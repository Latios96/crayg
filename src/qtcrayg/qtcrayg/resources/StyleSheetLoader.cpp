#include "StyleSheetLoader.h"
#include "Logger.h"
#include "qtcrayg/foundation/QtBase.h"
#include "utils/FileSystemUtils.h"
#include <QFontDatabase>
#include <filesystem>

namespace crayg {

void loadFonts() {
    QFontDatabase::addApplicationFont(":/fonts/Roboto/Roboto-Black.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto/Roboto-BlackItalic.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto/Roboto-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto/Roboto-BoldItalic.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto/Roboto-Italic.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto/Roboto-Light.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto/Roboto-LightItalic.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto/Roboto-Medium.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto/Roboto-MediumItalic.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto/Roboto-Thin.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto/Roboto-ThinItalic.ttf");
}

void StyleSheetLoader::loadAndApply() {
    loadFonts();

    if (mode == Mode::EMBEDDED) {
        applyEmbedded();
    } else {
        startWatching();
    }
}

void StyleSheetLoader::applyEmbedded() {
    QFile stylesheetFile(":/stylesheet.scss");
    if (!stylesheetFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Logger::error("Could not open stylesheet file");
    }
    const std::string &path = stylesheetFile.readAll().toStdString();
    compileAndApply(path);
}

void StyleSheetLoader::startWatching() {
    const QString stylesheetPath = getStyleSheetPathForWatching();

    watcher.addPath(stylesheetPath);

    QObject::connect(&watcher, &QFileSystemWatcher::fileChanged, [this](const QString &path) {
        const std::string inputPath = path.toStdString();
        const std::string fileContent = FileSystemUtils::readFileAsString(inputPath);
        compileAndApply(fileContent);
    });

    const std::string fileContent = FileSystemUtils::readFileAsString(stylesheetPath.toStdString());
    compileAndApply(fileContent);
    Logger::info("Started to watch stylesheet file {}", stylesheetPath);
}

void StyleSheetLoader::compileAndApply(const std::string &stylesheetString) {
    const std::string compiledStylesheet = compileSass(stylesheetString);
    if (compiledStylesheet.empty()) {
        return;
    }
    const QString &sheet = QString::fromStdString(compiledStylesheet);
    Logger::info("Applied stylesheet.");
    application.setStyleSheet(sheet);
}

QString StyleSheetLoader::getStyleSheetPathForWatching() {
    const std::filesystem::path pathToThisFile = __FILE__;
    const std::filesystem::path styleSheetFolder = pathToThisFile.parent_path();
    return QString::fromStdString((styleSheetFolder / "stylesheet.scss").string());
}

std::string StyleSheetLoader::compileSass(const std::string &stylesheetString) {
    Logger::info("Compiling stylesheet..");
    struct Sass_Options *options = sass_make_options();
    sass_option_set_output_style(options, SASS_STYLE_NESTED);
    sass_option_set_precision(options, 10);

    char *localBuffer = new char[stylesheetString.size() + 1];
    strcpy(localBuffer, stylesheetString.c_str());
    struct Sass_Data_Context *ctx = sass_make_data_context(localBuffer);
    struct Sass_Context *ctx_out = sass_data_context_get_context(ctx);
    sass_data_context_set_options(ctx, options);

    sass_compile_data_context(ctx);
    const int error = sass_context_get_error_status(ctx_out);
    std::string compiledStylesheet;
    if (error) {
        const std::string error = sass_context_get_error_message(ctx_out);
        Logger::error("Error when compiling stylesheet:\n{}", error);
    } else {
        compiledStylesheet = sass_context_get_output_string(ctx_out);
    }

    sass_delete_data_context(ctx);
    sass_delete_options(options);

    return compiledStylesheet;
}

}