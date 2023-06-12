#ifndef CRAYG_SRC_STANDALONEGUI_WIDGETS_GUITASKREPORTER_H_
#define CRAYG_SRC_STANDALONEGUI_WIDGETS_GUITASKREPORTER_H_

#include "utils/TaskReporter.h"
#include <QObject>

namespace crayg {

class TaskReporterQtSignalAdapter : public QObject {
    Q_OBJECT
  public:
    void emitTaskStarted(const TaskReporter::Task &task);
    void emitTaskFinished(const TaskReporter::Task &task);
    void emitTaskProgressUpdated(const TaskReporter::Task &task);
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

} // crayg

#endif // CRAYG_SRC_STANDALONEGUI_WIDGETS_GUITASKREPORTER_H_
