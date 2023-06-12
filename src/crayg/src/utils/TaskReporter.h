#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_TASKREPORTER_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_TASKREPORTER_H_

#include "Logger.h"
#include <chrono>
#include <fmt/chrono.h>
#include <optional>
#include <string>

namespace crayg {

class BaseTaskReporter {
  public:
    class TaskProgressController {
      public:
        TaskProgressController(const std::string &taskName, BaseTaskReporter &taskReporter);

        void iterationDone();

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

class TaskReporter : public BaseTaskReporter {
  protected:
    void onTaskStarted() override;

    void onTaskFinished() override;

    void onTaskProgressUpdated() override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_UTILS_TASKREPORTER_H_
