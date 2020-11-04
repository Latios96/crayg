
#include <QtWidgets/qapplication.h>
#include "FrameBufferWidget.h"

int main(int argc, char **argv) {
    QApplication a(argc, argv);

    FrameBufferWidget hello(nullptr);
    hello.show();

    return QApplication::exec();
}