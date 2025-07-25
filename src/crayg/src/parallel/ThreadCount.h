#pragma once

namespace crayg {

class ThreadCount {
  public:
    ThreadCount() : count(0){};

    explicit ThreadCount(int count) : count(count) {
    }

    int getThreadCount() const;

  private:
    int count;
};

}