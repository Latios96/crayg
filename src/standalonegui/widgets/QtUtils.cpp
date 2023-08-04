#include "QtUtils.h"
#include "Logger.h"
#include <QFile>

namespace crayg {

void applyStyleSheet(QApplication &application) {
    QFile stylesheetFile(":/stylesheet.css");
    if (!stylesheetFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Logger::error("Could not open stylesheet file");
    }
    QString stylesheet(stylesheetFile.readAll());
    application.setStyleSheet(stylesheet);
}

}