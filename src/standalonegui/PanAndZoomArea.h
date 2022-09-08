#ifndef CRAYG_SRC_STANDALONEGUI_PANANDZOOMAREA_H_
#define CRAYG_SRC_STANDALONEGUI_PANANDZOOMAREA_H_

#include <QtWidgets/qscrollarea.h>

namespace crayg {

class PanAndZoomArea : public QScrollArea {
 Q_OBJECT
 public:
    explicit PanAndZoomArea(QWidget *parent = nullptr);
    void setWidget(QWidget *widget);
 protected:
    void wheelEvent(QWheelEvent *event) override;
 private:
    int zoomFactor = 0;
    int newScrollValue(float mousePosition, float oldImageSize, int oldScrollbarValue, float newImageSize);
    QSize originalSize;
};

} // crayg

#endif //CRAYG_SRC_STANDALONEGUI_PANANDZOOMAREA_H_
