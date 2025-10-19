#pragma once

#include "crayg/foundation/logging/Logger.h"
#include <QApplication>
#include <QFile>
#include <QFileSystemWatcher>
#include <sass/context.h>

namespace crayg {

class StyleSheetLoader {
  public:
    enum class Mode { EMBEDDED, WATCH };

    StyleSheetLoader(Mode mode, QApplication &application) : mode(mode), application(application) {
    }

    void loadAndApply();

  private:
    void applyEmbedded();
    void startWatching();
    QString getStyleSheetPathForWatching();
    std::string compileSass(const std::string &inputPath);
    void compileAndApply(const std::string &inputPath);

    QFileSystemWatcher watcher;
    Mode mode;
    QApplication &application;
};

}
