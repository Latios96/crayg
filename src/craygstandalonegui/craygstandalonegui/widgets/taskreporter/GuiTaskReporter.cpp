#include "GuiTaskReporter.h"

namespace crayg {

void TaskReporterQtSignalAdapter::emitTaskStarted(const BaseTaskReporter::Task &task) {
    emit taskStarted(task);
}

void TaskReporterQtSignalAdapter::emitTaskFinished(const BaseTaskReporter::Task &task) {
    emit taskFinished(task);
}

void TaskReporterQtSignalAdapter::emitTaskProgressUpdated(const BaseTaskReporter::Task &task) {
    emit taskProgressUpdated(task);
}

void GuiTaskReporter::onTaskStarted() {
    TaskReporter::onTaskStarted();
    appController.emitTaskStarted(*currentTask);
}

void GuiTaskReporter::onTaskFinished() {
    TaskReporter::onTaskFinished();
    appController.emitTaskFinished(*currentTask);
}

void GuiTaskReporter::onTaskProgressUpdated() {
    TaskReporter::onTaskProgressUpdated();
    appController.emitTaskProgressUpdated(*currentTask);
}

GuiTaskReporter::GuiTaskReporter(TaskReporterQtSignalAdapter &appController) : appController(appController) {
}
}