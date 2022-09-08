#ifndef CRAYG_SRC_STANDALONEGUI_PANANDZOOMAREA_H_
#define CRAYG_SRC_STANDALONEGUI_PANANDZOOMAREA_H_

#include <QtWidgets/qscrollarea.h>
#include <ostream>
#include <fmt/ostream.h>
#include "Logger.h"

namespace crayg {

class ZoomFactor {
 public:
    ZoomFactor() = default;
    explicit ZoomFactor(int value);
    int getValue() const;
    float toFloat() const;
    float toPercentage() const;
    bool operator==(const ZoomFactor &rhs) const;
    bool operator!=(const ZoomFactor &rhs) const;
    ZoomFactor &operator++(int);
    ZoomFactor &operator--(int);
    friend std::ostream &operator<<(std::ostream &os, const ZoomFactor &factor);
 private:
    int value = 0;
};

class PanAndZoomArea : public QScrollArea {
 Q_OBJECT
 public:
    explicit PanAndZoomArea(QWidget *parent = nullptr);
    void setWidget(QWidget *widget);
    const QSize &getOriginalSize() const;
    void setOriginalSize(const QSize &originalSize);
 protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
 signals:
    void zoomFactorChanged(ZoomFactor zoomFactor);
 private:
    ZoomFactor zoomFactor;
    int newScrollValue(float mousePosition, float oldImageSize, int oldScrollbarValue, float newImageSize);
    QSize originalSize;
    void startMove(const QPoint &point);
    QPoint move(const QPoint &point);
    QPoint endMove(const QPoint &point);
    void applyMove(const QPoint point);
    bool isMoving = false;
    QPoint panStartPoint;
};

} // crayg

#endif //CRAYG_SRC_STANDALONEGUI_PANANDZOOMAREA_H_
