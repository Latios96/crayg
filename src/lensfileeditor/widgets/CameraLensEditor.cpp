#include "CameraLensEditor.h"
#include "crayg/scene/camera/realistic/lensio/LensFileReaderFactory.h"
#include "model/CameraLensModel.h"
#include "qtcrayg/widgets/QtWidgetsBuilderDsl.h"
#include <QHeaderView>
#include <QLabel>
#include <QTableView>

namespace crayg {

CameraLensEditor::CameraLensEditor() {
    setupUI();
}

void CameraLensEditor::setupUI() {
    const std::string lensFilePath = "C:\\workspace\\crayg\\resources\\lensfiles\\Panavision.fx";
    auto reader = LensFileReaderFactory::createLensFileReader(lensFilePath);
    cameraLens = std::make_unique<CameraLens>(reader->readFile(lensFilePath));

    auto tableView = new QTableView();
    tableView->setAlternatingRowColors(true);
    tableView->horizontalHeader()->setAlternatingRowColors(true);
    tableView->verticalHeader()->setAlternatingRowColors(true);
    CameraLensModel *cameraLensModel = new CameraLensModel(this, *cameraLens);
    tableView->setModel(cameraLensModel);
    auto grid = new QGridLayout();
    grid->addWidget(new QLabel("Name: "), 0, 0);
    grid->addWidget(new QLabel("test"), 0, 1);
    grid->addWidget(new QLabel("Focal Length: "), 1, 0);
    grid->addWidget(new QLabel("72.1"), 1, 1);

    auto layout = inVBox({
        new QLabel("<b>Metadata</b>"),
        inVBox({grid, addHStretch()}),
        inHBox({
            tableView,
            new QLabel("selected lens info"),
        }),
        new QLabel("Lens Design Drawing"),
    });
    setLayout(layout);
}

}