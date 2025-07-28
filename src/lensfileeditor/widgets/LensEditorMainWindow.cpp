#include "LensEditorMainWindow.h"
#include "Logger.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>

namespace crayg {
LensEditorMainWindow::LensEditorMainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
}

void LensEditorMainWindow::setupUI() {
    resize(QSize(1000, 750));
    setupActions();
    setupMenus();
}

void LensEditorMainWindow::setupActions() {
    newAction = new QAction("&New", this);
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip("Create a new file");
    QObject::connect(newAction, &QAction::triggered, []() { Logger::info("clicked"); });
}

void LensEditorMainWindow::setupMenus() {
    auto fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(newAction);
    fileMenu->addSeparator();
}
}