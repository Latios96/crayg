#include "StyleSheetLoader.h"
#include "QtBase.h"
#include <filesystem>

namespace crayg {
void StyleSheetLoader::loadAndApply() {
    if (mode == Mode::EMBEDDED) {
        applyEmbedded();
    } else {
        startWatching();
    }
}

void StyleSheetLoader::applyEmbedded() {
    QFile stylesheetFile(":/stylesheet.css");
    if (!stylesheetFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Logger::error("Could not open stylesheet file");
    }
    QString stylesheet(stylesheetFile.readAll());
    application.setStyleSheet(stylesheet);
}

void StyleSheetLoader::startWatching() {
    const QString stylesheetPath = getStyleSheetPathForWatching();

    watcher.addPath(stylesheetPath);

    QObject::connect(&watcher, &QFileSystemWatcher::fileChanged, [this](const QString &path) {
        Logger::info("Recompiling stylesheet..");

        const std::string inputPath = path.toStdString();
        compileAndApply(inputPath);
        Logger::info("Applied recompiled stylesheet");
    });

    compileAndApply(stylesheetPath.toStdString());
    Logger::info("Started to watch stylesheet file {}", stylesheetPath);
}

void StyleSheetLoader::compileAndApply(const std::string &inputPath) {
    const std::string compiledStylesheet = compileSass(inputPath);
    application.setStyleSheet(QString::fromStdString(compiledStylesheet));
}

QString StyleSheetLoader::getStyleSheetPathForWatching() {
    const std::filesystem::path pathToThisFile = __FILE__;
    const std::filesystem::path styleSheetFolder = pathToThisFile.parent_path();
    return QString::fromStdString((styleSheetFolder / "stylesheet.scss").string());
}

std::string StyleSheetLoader::compileSass(const std::string &inputPath) {
    struct Sass_Options *options = sass_make_options();
    sass_option_set_output_style(options, SASS_STYLE_NESTED);
    sass_option_set_precision(options, 10);

    struct Sass_File_Context *ctx = sass_make_file_context(inputPath.c_str());
    struct Sass_Context *ctx_out = sass_file_context_get_context(ctx);
    sass_option_set_input_path(options, inputPath.c_str());
    sass_file_context_set_options(ctx, options);

    sass_compile_file_context(ctx);
    sass_context_get_error_status(ctx_out);
    sass_context_get_error_message(ctx_out);
    std::string compiledStylesheet = sass_context_get_output_string(ctx_out);
    sass_delete_file_context(ctx);

    return compiledStylesheet;
}

} // crayg