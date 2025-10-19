#include "Initialization.h"
#include "crayg/foundation/executable/CraygMain.h"
#include "qtcrayg/foundation/QtMetaTypes.h"
#include "qtcrayg/resources/StyleSheetLoader.h"
#include "widgets/CameraLensEditor.h"
#include "widgets/LensEditorMainWindow.h"
#include <QLabel>

namespace crayg {

int craygMain(int argc, char **argv) {
    QApplication application(argc, argv);
    StyleSheetLoader styleSheetLoader(StyleSheetLoader::Mode::WATCH, application);
    styleSheetLoader.loadAndApply();

    registerQMetaTypes();

    CameraLensEditor *cameraLensEditor = new CameraLensEditor();

    LensEditorMainWindow *mainWindow = new LensEditorMainWindow(nullptr);
    mainWindow->setCentralWidget(cameraLensEditor);
    mainWindow->show();

    return QApplication::exec();
}

}

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(resources);
    CRAYG_MAIN_IMPL;
}