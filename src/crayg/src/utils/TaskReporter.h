#pragma once

#include "Logger.h"
#include "utils/EnumFormatter.h"
#include <chrono>
#include <fmt/chrono.h>
#include <optional>
#include <string>

namespace crayg {

class BaseTaskReporter {
  public:
    enum class IterationStatus { NO_PROGRESS_INCREMENT, PROGRESS_INCREMENT, LAST_ITERATION };

    class TaskProgressController {

      public:
        TaskProgressController(const std::string &taskName, BaseTaskReporter &taskReporter);

        IterationStatus iterationDone();

        std::chrono::seconds finish();

      private:
        const char *taskNameData;

        BaseTaskReporter &taskReporter;
        void requireCurrentTaskDidNotChange();
    };

    TaskProgressController startTask(const std::string &taskName, int maxIterations);

    struct Task {
        Task();
        Task(const std::string &name, int maxIterations);
        Task(const Task &task);
        Task &operator=(const Task &other);

        std::string name;
        std::chrono::time_point<std::chrono::steady_clock> startTime;
        int maxIterations;
        std::atomic<int> iterationsDone;

        int progress();
        std::chrono::seconds elapsedTime();
        std::chrono::seconds estimatedTimeRemaining();
        ~Task() = default;
    };

  protected:
    virtual void onTaskStarted() = 0;
    virtual void onTaskFinished() = 0;
    virtual void onTaskProgressUpdated() = 0;

    std::optional<Task> currentTask;
};

class NullTaskReporter : public BaseTaskReporter {
  protected:
    void onTaskStarted() override {
    }

    void onTaskFinished() override {
    }

    void onTaskProgressUpdated() override {
    }
};

class TaskReporter : public BaseTaskReporter {
  protected:
    void onTaskStarted() override;

    void onTaskFinished() override;

    void onTaskProgressUpdated() override;
};

}

CRAYG_FMT_ENUM_FORMATTER_H(crayg::BaseTaskReporter::IterationStatus);
