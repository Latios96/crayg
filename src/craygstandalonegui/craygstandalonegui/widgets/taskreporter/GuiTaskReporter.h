#pragma once

// clang-format off
#include <QObject>
// clang-format on
#include "crayg/foundation/progress/TaskReporter.h"

namespace crayg {

class TaskReporterQtSignalAdapter : public QObject {
    Q_OBJECT
  public:
    void emitTaskStarted(const BaseTaskReporter::Task &task);
    void emitTaskFinished(const BaseTaskReporter::Task &task);
    void emitTaskProgressUpdated(const BaseTaskReporter::Task &task);
  signals:
    void taskStarted(BaseTaskReporter::Task task);
    void taskFinished(BaseTaskReporter::Task task);
    void taskProgressUpdated(BaseTaskReporter::Task task);
};

class GuiTaskReporter : public TaskReporter {
  public:
    explicit GuiTaskReporter(TaskReporterQtSignalAdapter &appController);

  protected:
    void onTaskStarted() override;

    void onTaskFinished() override;

    void onTaskProgressUpdated() override;

    TaskReporterQtSignalAdapter &appController;
};

}
