#include "utils/TaskReporter.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("BaseTaskReporter::Task::progress") {
    BaseTaskReporter::Task task("testTask", 10);

    SECTION("should return 0%") {
        REQUIRE(task.progress() == 0);
    }
    SECTION("should return 20%") {
        task.iterationsDone = 2;

        REQUIRE(task.progress() == 20);
    }
    SECTION("should return 50%") {
        task.iterationsDone = 5;

        REQUIRE(task.progress() == 50);
    }
    SECTION("should return 100%") {
        task.iterationsDone = 10;

        REQUIRE(task.progress() == 100);
    }

    SECTION("should return 0% for finished task with 0 max iterations") {
        BaseTaskReporter::Task task("testTask", 0);

        REQUIRE(task.progress() == 0);
    }
}

TEST_CASE("BaseTaskReporter::Task::elapsedTime") {

    SECTION("should return 0 elapsed time") {
        BaseTaskReporter::Task task("testTask", 10);

        REQUIRE(task.elapsedTime() <= std::chrono::seconds(1));
    }

    SECTION("should return 10s elapsed time") {
        BaseTaskReporter::Task task("testTask", 10);
        task.startTime = std::chrono::steady_clock::now() - std::chrono::seconds(10);

        REQUIRE(task.elapsedTime() <= std::chrono::seconds(10));
    }
}

TEST_CASE("BaseTaskReporter::Task::estimatedTimeRemaining") {

    SECTION("should return -1 estimated time remaining for unstarted task") {
        BaseTaskReporter::Task task("testTask", 10);
        task.startTime = std::chrono::steady_clock::now() - std::chrono::seconds(10);

        REQUIRE(task.estimatedTimeRemaining() == std::chrono::seconds(-1));
    }

    SECTION("should return 5s estimated time remaining for half finished task") {
        BaseTaskReporter::Task task("testTask", 10);
        task.startTime = std::chrono::steady_clock::now() - std::chrono::seconds(10);
        task.iterationsDone = 5;

        REQUIRE(task.estimatedTimeRemaining() == std::chrono::seconds(10));
    }

    SECTION("should return 0 estimated time remaining for finished task") {
        BaseTaskReporter::Task task("testTask", 10);
        task.startTime = std::chrono::steady_clock::now() - std::chrono::seconds(10);
        task.iterationsDone = 10;

        REQUIRE(task.estimatedTimeRemaining() == std::chrono::seconds(0));
    }
}

class TestingTaskReporter : public BaseTaskReporter {
  protected:
    void onTaskStarted() override {
        onTaskStartedCalled = true;
    }

    void onTaskFinished() override {
        onTaskFinishedCalled = true;
    }

    void onTaskProgressUpdated() override {
        onTaskProgressUpdatedCalled = true;
    }

  public:
    bool onTaskStartedCalled = false;
    bool onTaskFinishedCalled = false;
    bool onTaskProgressUpdatedCalled = false;
};

TEST_CASE("BaseTaskReporter::startTask") {

    SECTION("should start new task") {
        TestingTaskReporter testingTaskReporter;
        auto progressController = testingTaskReporter.startTask("test task", 10);

        REQUIRE(testingTaskReporter.onTaskStartedCalled);
    }

    SECTION("should throw if there is already a task running") {
        TestingTaskReporter testingTaskReporter;
        testingTaskReporter.startTask("test task", 10);
        REQUIRE_THROWS_AS(testingTaskReporter.startTask("test task", 10), std::runtime_error);
    }
}

TEST_CASE("BaseTaskReporter::TaskProgressController::iterationDone") {

    SECTION("should not call onTaskProgressUpdated, if not a new percentage is reached") {
        TestingTaskReporter testingTaskReporter;
        auto progressController = testingTaskReporter.startTask("test task", 200);

        progressController.iterationDone();

        REQUIRE_FALSE(testingTaskReporter.onTaskProgressUpdatedCalled);
    }

    SECTION("should call onTaskProgressUpdated if a new percentage is reached") {
        TestingTaskReporter testingTaskReporter;
        auto progressController = testingTaskReporter.startTask("test task", 200);

        progressController.iterationDone();
        progressController.iterationDone();

        REQUIRE(testingTaskReporter.onTaskProgressUpdatedCalled);
    }
}

TEST_CASE("BaseTaskReporter::TaskProgressController::finish") {

    SECTION("should call onTaskFinishedCalled and clear current task") {
        TestingTaskReporter testingTaskReporter;
        auto progressController = testingTaskReporter.startTask("test task", 200);

        progressController.finish();

        REQUIRE(testingTaskReporter.onTaskFinishedCalled);
        testingTaskReporter.startTask("test task 2", 200); // cleared task means we can start a new one..
    }
}

}