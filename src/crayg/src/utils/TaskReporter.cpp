#include "TaskReporter.h"
#include "RemainingTimeCalculator.h"
#include "utils/Exceptions.h"

namespace crayg {

BaseTaskReporter::Task::Task() : Task("", 0) {
}

BaseTaskReporter::Task::Task(const std::string &name, int maxIterations)
    : name(name), startTime(std::chrono::steady_clock::now()), maxIterations(maxIterations), iterationsDone(0) {
}

BaseTaskReporter::Task::Task(const BaseTaskReporter::Task &task)
    : name(task.name), startTime(task.startTime), maxIterations(task.maxIterations),
      iterationsDone(task.iterationsDone.load()) {
}

int BaseTaskReporter::Task::progress() {
    const float progressInPercent = static_cast<float>(iterationsDone) / (static_cast<float>(maxIterations)) * 100;
    return std::clamp(static_cast<int>(progressInPercent), 0, 100);
}

BaseTaskReporter::Task &BaseTaskReporter::Task::operator=(const BaseTaskReporter::Task &other) {
    name = other.name;
    startTime = other.startTime;
    maxIterations = other.maxIterations;
    iterationsDone = other.iterationsDone.load();
    return *this;
}

std::chrono::seconds BaseTaskReporter::Task::elapsedTime() {
    const auto elapsed = std::chrono::steady_clock::now() - startTime;
    return std::chrono::duration_cast<std::chrono::seconds>(elapsed);
}

std::chrono::seconds BaseTaskReporter::Task::estimatedTimeRemaining() {
    RemainingTimeCalculator remainingTimeCalculator(startTime);
    return remainingTimeCalculator.getRemainingSecondsByProgress(progress());
}

void BaseTaskReporter::TaskProgressController::requireCurrentTaskDidNotChange() {
    if (taskReporter.currentTask->name.data() != taskNameData) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Task changed to {}, unsupported", taskReporter.currentTask->name);
    }
}

BaseTaskReporter::TaskProgressController::TaskProgressController(const std::string &taskName,
                                                                 BaseTaskReporter &taskReporter)
    : taskNameData(taskName.data()), taskReporter(taskReporter) {
}

BaseTaskReporter::IterationStatus BaseTaskReporter::TaskProgressController::iterationDone() {
    requireCurrentTaskDidNotChange();
    const int oldProgress = taskReporter.currentTask->progress();
    taskReporter.currentTask->iterationsDone++;
    const int newProgress = taskReporter.currentTask->progress();
    if (newProgress > oldProgress) {
        taskReporter.onTaskProgressUpdated();
        return newProgress == 100 ? IterationStatus::LAST_ITERATION : IterationStatus::PROGRESS_INCREMENT;
    }
    return IterationStatus::NO_PROGRESS_INCREMENT;
}

std::chrono::seconds BaseTaskReporter::TaskProgressController::finish() {
    requireCurrentTaskDidNotChange();
    taskReporter.onTaskFinished();
    const auto elapsedTime = taskReporter.currentTask->elapsedTime();
    taskReporter.currentTask = std::nullopt;
    return elapsedTime;
}

BaseTaskReporter::TaskProgressController BaseTaskReporter::startTask(const std::string &taskName, int maxIterations) {
    if (currentTask) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Can't start a new task, a task with name {} is already running",
                                          currentTask->name);
    }
    currentTask = std::make_optional(Task(taskName, maxIterations));
    onTaskStarted();
    return {currentTask->name, *this};
}

void TaskReporter::onTaskStarted() {
    Logger::info("{}..", currentTask->name);
}

void TaskReporter::onTaskFinished() {
    Logger::info("{} took {:%Hh %Mm %Ss}.", currentTask->name, currentTask->elapsedTime());
}

void TaskReporter::onTaskProgressUpdated() {
    const auto elapsedTime = currentTask->elapsedTime();
    const auto estimatedTimeRemaining = currentTask->estimatedTimeRemaining();
    const auto estimatedTotalTime = elapsedTime + estimatedTimeRemaining;
    Logger::info("{} done by {}%, elapsed time: {:%Hh %Mm %Ss}, remaining time: {:%Hh %Mm %Ss}, estimated total time: "
                 "{:%Hh %Mm %Ss}",
                 currentTask->name, currentTask->progress(), elapsedTime, estimatedTimeRemaining, estimatedTotalTime);
}
} // crayg