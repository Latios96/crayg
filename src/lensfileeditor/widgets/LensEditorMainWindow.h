#pragma once

#include <QMainWindow>

namespace crayg {

class LensEditorMainWindow : public QMainWindow {
    Q_OBJECT
  public:
    LensEditorMainWindow(QWidget *parent);
    void setupUI();
    void setupActions();
    void setupMenus();

  private:
    QAction *newAction;
};
} // crayg
