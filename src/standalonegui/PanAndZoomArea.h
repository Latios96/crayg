#ifndef CRAYG_SRC_STANDALONEGUI_PANANDZOOMAREA_H_
#define CRAYG_SRC_STANDALONEGUI_PANANDZOOMAREA_H_

#include <QtWidgets/qscrollarea.h>
#include <ostream>
#include <fmt/ostream.h>

namespace crayg {

class ZoomFactor {
 public:
    ZoomFactor() = default;
    explicit ZoomFactor(int value);
    int getValue() const;
    float toPercentage() const;
    bool operator==(const ZoomFactor &rhs) const;
    bool operator!=(const ZoomFactor &rhs) const;
    ZoomFactor &ZoomFactor::operator++(int);
    ZoomFactor &ZoomFactor::operator--(int);
    friend std::ostream &operator<<(std::ostream &os, const ZoomFactor &factor);
 private:
    int value = 0;
};

class PanAndZoomArea : public QScrollArea {
 Q_OBJECT
 public:
    explicit PanAndZoomArea(QWidget *parent = nullptr);
    void setWidget(QWidget *widget);
 protected:
    void wheelEvent(QWheelEvent *event) override;
 signals:
    void zoomFactorChanged(ZoomFactor zoomFactor);
 private:
    ZoomFactor zoomFactor;
    int newScrollValue(float mousePosition, float oldImageSize, int oldScrollbarValue, float newImageSize);
    QSize originalSize;
};

} // crayg

#endif //CRAYG_SRC_STANDALONEGUI_PANANDZOOMAREA_H_
