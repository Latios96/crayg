#pragma once

#include "Logger.h"
#include <QtWidgets/qscrollarea.h>
#include <fmt/ostream.h>
#include <ostream>

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
    void setOriginalSize(const QSize &originalSize);
    ZoomFactor getZoomFactor() const;

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
    void startMove(const QPoint &point);
    QPoint move(const QPoint &point);
    QPoint endMove(const QPoint &point);
    void applyMove(const QPoint point);
    bool isMoving = false;
    QPoint panStartPoint;
};

}

template <> struct fmt::formatter<crayg::ZoomFactor> : ostream_formatter {};
