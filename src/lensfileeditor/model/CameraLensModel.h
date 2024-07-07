#ifndef CRAYG_SRC_STANDALONEGUI_WIDGETS_MYTABLEMODEL_H_
#define CRAYG_SRC_STANDALONEGUI_WIDGETS_MYTABLEMODEL_H_
#include "qtcrayg/utils/QtUtils.h"
#include "scene/camera/realistic/CameraLens.h"
#include <QAbstractTableModel>

namespace crayg {

class CameraLensModel : public QAbstractTableModel {
    Q_OBJECT

  public:
    explicit CameraLensModel(QObject *parent, CameraLens &cameraLens)
        : QAbstractTableModel(parent), cameraLens(cameraLens) {
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return cameraLens.elements.size();
    }
    enum class Columns {
        CURVATURE_RADIUS,
        THICKNESS,
        IOR,
        HOUSING_RADIUS,
        ABBE_NUMBER,
        MATERIAL,
        GEOMETRY,
        COLUMN_COUNT
    };

    int columnCount(const QModelIndex &parent) const override {
        return static_cast<int>(CameraLensModel::Columns::COLUMN_COUNT);
    }

    QVariant data(const QModelIndex &index, int role) const override {
        switch (role) {
        case Qt::DisplayRole:
            return handleDisplayRole(index);
        }
        return QVariant();
    }

    QVariant handleDisplayRole(const QModelIndex &index) const {
        const int elementIndex = index.row();
        if (elementIndex < 0 || elementIndex >= cameraLens.elements.size()) {
            return {};
        }

        const Columns column = static_cast<Columns>(index.column());
        switch (column) {
        case Columns::CURVATURE_RADIUS:
            return cameraLens.elements[elementIndex].curvatureRadius;
        case Columns::THICKNESS:
            return cameraLens.elements[elementIndex].thickness;
        case Columns::IOR:
            return cameraLens.elements[elementIndex].ior;
        case Columns::HOUSING_RADIUS:
            return cameraLens.elements[elementIndex].apertureRadius;
        case Columns::ABBE_NUMBER:
            return cameraLens.elements[elementIndex].material.abbeNo;
        case Columns::MATERIAL:
            return qformat("{}", cameraLens.elements[elementIndex].material.id);
        case Columns::GEOMETRY:
            return qformat("{}", cameraLens.elements[elementIndex].geometry);
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (orientation == Qt::Vertical || role != Qt::DisplayRole) {
            return QAbstractTableModel::headerData(section, orientation, role);
        }
        const CameraLensModel::Columns column = static_cast<CameraLensModel::Columns>(section);
        switch (column) {
        case Columns::CURVATURE_RADIUS:
            return "Radius";
        case Columns::THICKNESS:
            return "Thickness";
        case Columns::IOR:
            return "IOR";
        case Columns::HOUSING_RADIUS:
            return "Housing Radius";
        case Columns::ABBE_NUMBER:
            return "Abbe No";
        case Columns::MATERIAL:
            return "Material";
        case Columns::GEOMETRY:
            return "Geometry";
        }
        return QVariant();
    }

  private:
    CameraLens &cameraLens;
};
}

#endif // CRAYG_SRC_STANDALONEGUI_WIDGETS_MYTABLEMODEL_H_
